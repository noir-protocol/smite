// This file is part of NOIR.
//
// Copyright (c) 2022 Haderech Pte. Ltd.
// SPDX-License-Identifier: AGPL-3.0-or-later
//
#include <catch2/catch_all.hpp>
#include <noir/codec/scale.h>
#include <noir/common/hex.h>
#include <noir/common/thread_pool.h>
#include <noir/tx_pool/LRU_cache.h>
#include <noir/tx_pool/tx_pool.h>
#include <noir/tx_pool/unapplied_tx_queue.h>
#include <algorithm>

using namespace noir;
using namespace noir::consensus;
using namespace noir::tx_pool;

namespace test_detail {

static address_type str_to_addr(const std::string& str) {
  address_type addr(str.begin(), str.end());
  return addr;
}

class test_helper {
private:
  uint64_t tx_id = 0;
  uint64_t nonce = 0;
  uint64_t height = 0;

  std::mutex mutex;

  std::random_device random_device;
  std::mt19937 generator{random_device()};

  std::shared_ptr<class tx_pool> tp = nullptr;

  class test_application : public application::base_application {
    std::mutex mutex_;

  public:
    consensus::response_check_tx res_{.sender = str_to_addr("user"), .nonce = 0};

    consensus::response_check_tx check_tx() override {
      std::lock_guard lock(mutex_);
      consensus::response_check_tx res = res_;
      res_.nonce++;
      return res;
    }

    void set_nonce(uint64_t nonce) {
      std::lock_guard lock(mutex_);
      res_.nonce = nonce;
    }

    void set_gas(uint64_t gas) {
      std::lock_guard lock(mutex_);
      res_.gas_wanted = gas;
    }
  };

  std::shared_ptr<test_application> test_app_conn = std::make_shared<test_application>();

public:
  auto new_tx() {
    std::lock_guard<std::mutex> lock(mutex);
    return codec::scale::encode(tx_id++);
  }

  auto new_txs(uint count) {
    std::vector<consensus::tx> txs;
    for (uint i = 0; i < count; i++) {
      txs.push_back(new_tx());
    }

    for (auto tx : txs) {
      REQUIRE(tx.size() != 0);
    }
    return txs;
  }

  auto make_random_wrapped_tx(const std::string& sender) {
    wrapped_tx new_wrapped_tx;
    new_wrapped_tx.sender = str_to_addr(sender);
    new_wrapped_tx.gas = rand_gas();

    std::lock_guard<std::mutex> lock(mutex);
    new_wrapped_tx.tx_data = codec::scale::encode(tx_id++);
    new_wrapped_tx.nonce = nonce++;
    new_wrapped_tx.height = height++;
    return new_wrapped_tx;
  }

  void reset_tx_id() {
    std::lock_guard<std::mutex> lock(mutex);
    tx_id = 0;
  }

  uint64_t rand_gas(uint64_t max = 0xFFFF, uint64_t min = 0) {
    std::uniform_int_distribution<uint64_t> dist_gas{min, max};
    return dist_gas(generator);
  }

  class tx_pool& make_tx_pool() {
    return make_tx_pool(config{});
  }

  class tx_pool& make_tx_pool(config cfg) {
    auto proxy_app = std::make_shared<app_connection>();
    proxy_app->application = test_app_conn;
    tp = std::make_shared<noir::tx_pool::tx_pool>(cfg, proxy_app, 0);
    tp->start();
    return *tp;
  }

  void set_gas(uint64_t gas_wanted) {
    test_app_conn->set_gas(gas_wanted);
  }

  void set_nonce(uint64_t nonce) {
    test_app_conn->set_nonce(nonce);
  }
};

} // namespace test_detail

using namespace test_detail;

TEST_CASE("Tx queue basic test", "[tx_pool][unapplied_tx_queue]") {
  auto test_helper = std::make_unique<::test_helper>();
  unapplied_tx_queue tx_queue;

  const uint64_t tx_count = 10;
  wrapped_tx_ptrs wtxs;
  for (auto i = 0; i < tx_count; i++) {
    wtxs.push_back(std::make_shared<::wrapped_tx>(test_helper->make_random_wrapped_tx("user")));
  }

  // Add tx
  for (auto& wtx : wtxs) {
    CHECK(tx_queue.add_tx(wtx));
  }
  CHECK(tx_queue.size() == tx_count);

  SECTION("Add same tx id") { // fail case
    auto wtx = wtxs[0];
    wtx->nonce = wtxs[tx_count - 1]->nonce + 1;
    CHECK(tx_queue.add_tx(wtx) == false);
    CHECK(tx_queue.size() == tx_count);
    CHECK(tx_queue.get_tx(wtxs[0]->id()));
  }

  SECTION("Has") {
    for (auto& wtx : wtxs) {
      CHECK(tx_queue.has(wtx->id()));
    }
  }

  SECTION("Get") {
    for (auto& wtx : wtxs) {
      CHECK(tx_queue.get_tx(wtx->id()).has_value());
    }
  }

  SECTION("Erase tx") {
    for (auto& wtx : wtxs) {
      CHECK(tx_queue.erase(wtx->id()));
    }
    CHECK(tx_queue.empty());

    // fail case
    for (auto& wtx : wtxs) {
      CHECK(tx_queue.erase(wtx->id()) == false);
    }
    CHECK(tx_queue.empty());
  }

  SECTION("Erase tx by iterator") {
    std::for_each(tx_queue.begin(), tx_queue.end(), [&](auto& itr) { CHECK(tx_queue.erase(itr.id())); });
    CHECK(tx_queue.empty());
  }

  SECTION("Flush") {
    tx_queue.clear();
    CHECK(tx_queue.size() == 0);
    CHECK(tx_queue.empty());
  }
}

TEST_CASE("Fully add/erase tx", "[tx_pool][unapplied_tx_queue]") {
  auto test_helper = std::make_unique<::test_helper>();
  uint64_t tx_count = 10000;
  uint64_t queue_size = 0;
  wrapped_tx_ptrs wtxs;
  for (uint64_t i = 0; i < tx_count; i++) {
    wtxs.push_back(std::make_shared<::wrapped_tx>(test_helper->make_random_wrapped_tx("user")));
  }

  for (auto& wtx : wtxs) {
    queue_size += unapplied_tx_queue::bytes_size(wtx);
  }

  auto tx_queue = std::make_unique<unapplied_tx_queue>(queue_size);
  for (auto& wtx : wtxs) {
    CHECK(tx_queue->add_tx(wtx));
  }
  CHECK(tx_queue->size() == tx_count);

  for (auto& wtx : wtxs) {
    CHECK(tx_queue->erase(wtx->id()));
  }
  CHECK(tx_queue->empty());
}

TEST_CASE("Indexing", "[tx_pool][unapplied_tx_queue]") {
  auto test_helper = std::make_unique<::test_helper>();
  uint64_t tx_count = 10000;
  uint64_t user_count = tx_count / 100;
  uint64_t queue_size = config{}.max_tx_bytes * tx_count;
  auto tx_queue = std::make_unique<unapplied_tx_queue>(queue_size);

  for (uint64_t i = 0; i < tx_count; i++) {
    CHECK(tx_queue->add_tx(
      std::make_shared<::wrapped_tx>(test_helper->make_random_wrapped_tx("user" + std::to_string(i / user_count)))));
  }
  CHECK(tx_queue->size() == tx_count);

  SECTION("by nonce") {
    auto tx = test_helper->make_random_wrapped_tx("Alice");
    tx_queue->add_tx(std::make_shared<::wrapped_tx>(tx));
    auto tx_ptr = tx_queue->get_tx(tx.sender, tx.nonce);
    CHECKED_IF(!tx_ptr.has_value()) {
      CHECK(tx_ptr.value()->nonce == tx.nonce);
    }
  }

  SECTION("a specific sender's txs") {
    SECTION("all txs") {
      uint64_t tx_count_per_user = tx_count / user_count;
      for (uint64_t i = 0; i < user_count; i++) {
        address_type sender = str_to_addr("user" + std::to_string(i));
        auto begin = tx_queue->begin(sender);
        auto end = tx_queue->end(sender);

        uint64_t count = 0;
        for (auto itr = begin; itr != end; itr++) {
          count++;
        }
        CHECK(count == tx_count_per_user);
      }
    }
  }

  SECTION("ordering") {
    SECTION("ascending") {
      auto begin = tx_queue->begin<unapplied_tx_queue::by_gas>();
      auto end = tx_queue->end<unapplied_tx_queue::by_gas>();

      uint64_t prev_gas = 0;
      for (auto itr = begin; itr != end; itr++) {
        CHECK(itr->gas() >= prev_gas);
        prev_gas = itr->gas();
      }
    }

    SECTION("descending") {
      auto rbegin = tx_queue->rbegin<unapplied_tx_queue::by_gas>();
      auto rend = tx_queue->rend<unapplied_tx_queue::by_gas>();

      uint64_t prev_gas = std::numeric_limits<uint64_t>::max();
      for (auto itr = rbegin; itr != rend; itr++) {
        CHECK(itr->gas() <= prev_gas);
        prev_gas = itr->gas();
      }
    }
  }

  SECTION("bound") {
    uint64_t lowest = 1000;
    uint64_t highest = 50000;
    auto begin = tx_queue->begin<unapplied_tx_queue::by_gas>(lowest);
    auto end = tx_queue->end<unapplied_tx_queue::by_gas>(highest);

    for (auto itr = begin; itr != end; itr++) {
      CHECK(lowest <= itr->gas());
      CHECK(itr->gas() <= highest);
    }

    auto rbegin = tx_queue->rbegin<unapplied_tx_queue::by_gas>(highest);
    auto rend = tx_queue->rend<unapplied_tx_queue::by_gas>(lowest);

    for (auto itr = rbegin; itr != rend; itr++) {
      CHECK(lowest <= itr->gas());
      CHECK(itr->gas() <= highest);
    }
  }
}

TEST_CASE("Push/Get tx", "[tx_pool]") {
  auto test_helper = std::make_unique<::test_helper>();
  auto& tp = test_helper->make_tx_pool();

  auto push_tx = [&](uint64_t count, bool sync = true) {
    std::vector<std::optional<std::future<bool>>> res_vec;
    for (uint64_t i = 0; i < count; i++) {
      res_vec.push_back(tp.check_tx(test_helper->new_tx(), sync));
    }
    return res_vec;
  };

  SECTION("sync") {
    auto res_push = push_tx(100);
    for (auto& r : res_push) {
      CHECKED_IF(r.has_value()) {
        CHECK(r.value().get());
      }
    }

    // fail case : same tx_id
    auto txs = tp.reap_max_txs(100);
    for (auto& tx : txs) {
      CHECK(!tp.check_tx(tx, true).has_value());
    }

    txs = tp.reap_max_txs(100);
    CHECK(txs.size() == 100);
  }

  SECTION("async") {
    uint64_t max_thread_num = 10;
    auto thread = std::make_unique<named_thread_pool>("test_thread", max_thread_num);

    SECTION("multi thread add") {
      uint64_t thread_num = std::min<uint64_t>(5, max_thread_num);
      uint64_t total_tx_num = 1000;
      std::atomic<uint64_t> token = thread_num;
      std::future<std::vector<std::optional<std::future<bool>>>> res[thread_num];
      uint64_t tx_num_per_thread = total_tx_num / thread_num;
      for (uint64_t t = 0; t < thread_num; t++) {
        res[t] = async_thread_pool(thread->get_executor(), [&]() {
          token.fetch_sub(1, std::memory_order_seq_cst);
          while (token.load(std::memory_order_seq_cst)) {
          } // wait other thread
          return push_tx(tx_num_per_thread, false);
        });
      }

      for (uint64_t t = 0; t < thread_num; t++) {
        uint64_t added_tx = 0;
        auto result = res[t].get();
        for (auto& r : result) {
          CHECKED_IF(r.has_value()) {
            CHECKED_IF(r.value().get()) {
              added_tx++;
            }
          }
        }
        CHECK(added_tx == tx_num_per_thread);
      }

      CHECK(tp.size() == total_tx_num);
    }

    SECTION("1 thread add / 1 thread get") {
      std::atomic<uint64_t> token = 2;

      auto push_res = async_thread_pool(thread->get_executor(), [&]() {
        token.fetch_sub(1, std::memory_order_seq_cst);
        while (token.load(std::memory_order_seq_cst)) {
        } // wait other thread
        return push_tx(1000, false);
      });

      auto get_res = async_thread_pool(thread->get_executor(), [&]() {
        token.fetch_sub(1, std::memory_order_seq_cst);
        while (token.load(std::memory_order_seq_cst)) {
        } // wait other thread

        uint64_t get_count = 0;
        while (get_count < 1000) {
          auto txs = tp.reap_max_txs(1000 - get_count);
          get_count += txs.size();
        }
        return get_count;
      });

      push_res.wait();
      auto res = push_res.get();
      for (auto& r : res) {
        CHECKED_IF(r.has_value()) {
          CHECK(r.value().get());
        }
      }

      CHECK(get_res.get() == 1000);
    }

    SECTION("1 thread add / 2 thread get") {
      std::atomic<uint64_t> token = 3;
      auto push_res = async_thread_pool(thread->get_executor(), [&]() {
        token.fetch_sub(1, std::memory_order_seq_cst);
        while (token.load(std::memory_order_seq_cst)) {
        } // wait other thread
        return push_tx(1000, false);
      });

      std::future<uint64_t> get_res[2];
      for (auto& res : get_res) {
        res = async_thread_pool(thread->get_executor(), [&]() {
          token.fetch_sub(1, std::memory_order_seq_cst);
          while (token.load(std::memory_order_seq_cst)) {
          } // wait other thread

          uint64_t get_count = 0;
          while (get_count < 500) {
            auto txs = tp.reap_max_txs(500 - get_count);
            get_count += txs.size();
          }
          return get_count;
        });
      }

      push_res.wait();
      auto res = push_res.get();
      for (auto& r : res) {
        CHECKED_IF(r.has_value()) {
          CHECK(r.value().get());
        }
      }

      uint64_t get_count = 0;
      get_count += get_res[0].get();
      get_count += get_res[1].get();
      CHECK(get_count == 1000);
    }
  }
}

TEST_CASE("Reap tx using max bytes & gas", "[tx_pool]") {
  auto test_helper = std::make_unique<::test_helper>();
  auto& tp = test_helper->make_tx_pool();

  const uint64_t tx_count = 10000;
  for (auto i = 0; i < tx_count; i++) {
    CHECK(tp.check_tx(test_helper->new_tx(), true)->get());
  }

  uint tc = 100;
  for (uint i = 0; i < tc; i++) {
    uint64_t max_bytes = 1000;
    uint64_t max_gas = test_helper->rand_gas(1000000, 100000);
    auto txs = tp.reap_max_bytes_max_gas(max_bytes, max_gas);
    uint64_t total_bytes = 0;
    for (auto& tx : txs) {
      total_bytes += tx.size();
    }
    CHECK(total_bytes <= max_bytes);
  }
}

TEST_CASE("Update", "[tx_pool]") {
  auto test_helper = std::make_unique<::test_helper>();

  const uint64_t tx_count = 10;

  auto put_tx = [&](class tx_pool& tp, std::vector<tx> txs) {
    for (auto& tx : txs) {
      auto res = tp.check_tx(tx, true);
      CHECKED_IF(res.has_value()) {
        CHECK(res.value().get());
      }
    }
  };

  SECTION("Erase committed tx") {
    auto& tp = test_helper->make_tx_pool();
    auto txs = test_helper->new_txs(tx_count);
    put_tx(tp, txs);
    std::vector<consensus::response_deliver_tx> res;
    res.resize(tx_count);
    CHECK(tp.update(0, txs, res));
    CHECK(tp.empty());
  }

  SECTION("Erase block height expired tx") {
    config config{
      .ttl_num_blocks = 10,
    };
    auto& tp = test_helper->make_tx_pool(config);
    std::vector<consensus::response_deliver_tx> res;
    res.resize(tx_count);
    std::vector<tx> empty_txs;
    for (uint64_t i = 0; i < tx_count; i++) {
      CHECK(tp.update(i, empty_txs, res));
      auto txs = test_helper->new_txs(1);
      put_tx(tp, txs);
    }

    for (uint64_t i = 0; i < tx_count; i++) {
      CHECK(tp.update(config.ttl_num_blocks + i, empty_txs, res));
      CHECK(tp.size() == tx_count - i - 1);
    }
    CHECK(tp.empty());
  }

  SECTION("Erase time expired tx") {
    config config{
      .ttl_duration = std::chrono::microseconds(100000LL).count(), // 100 msec
    };
    auto& tp = test_helper->make_tx_pool(config);
    auto txs = test_helper->new_txs(tx_count);
    put_tx(tp, txs);
    std::vector<consensus::response_deliver_tx> res;
    res.resize(tx_count);
    std::vector<consensus::tx> empty_txs;

    usleep(100000LL); // sleep 100 msec
    CHECK(tp.update(0, empty_txs, res));
    CHECK(tp.empty());
  }
}

TEST_CASE("Nonce override", "[tx_pool]") {
  auto test_helper = std::make_unique<::test_helper>();
  config config;
  auto& tp = test_helper->make_tx_pool(config);

  auto tx1 = test_helper->new_tx();
  CHECK(tp.check_tx(tx1, true).value().get());

  auto tx2 = test_helper->new_tx();
  test_helper->set_nonce(0);
  CHECK(!tp.check_tx(tx2, true).value().get());

  test_helper->set_nonce(0);
  test_helper->set_gas(config.gas_price_bump);
  CHECK(tp.check_tx(tx2, true).value().get());
}

TEST_CASE("Cache basic test", "[tx_pool][LRU_cache]") {
  auto test_helper = std::make_unique<::test_helper>();
  uint tx_count = 1000;
  uint cache_size = 1000;

  LRU_cache<tx_id_type, consensus::tx> c{cache_size};

  struct test_tx {
    tx tx;
    tx_id_type id;
  };
  std::vector<test_tx> txs;

  for (uint64_t i = 0; i < tx_count; i++) {
    test_tx test_tx;
    test_tx.tx = test_helper->new_tx();
    test_tx.id = get_tx_id(test_tx.tx);
    c.put(test_tx.id, test_tx.tx);
    txs.push_back(test_tx);
  }

  SECTION("put") {
    CHECK(c.size() == tx_count);
    for (auto& tx : txs) {
      CHECK(c.has(tx.id));
    }

    // new tx, replace the oldest tx in cache
    auto tx = test_helper->new_tx();
    c.put(get_tx_id(tx), tx); // tx0 is replaced by new one
    CHECK(c.size() == tx_count);
    CHECK(c.has(get_tx_id(tx)));
    CHECK(!c.has(txs[0].id));

    // put again tx1
    c.put(txs[1].id, txs[1].tx);
    tx = test_helper->new_tx();
    c.put(get_tx_id(tx), tx); // tx2 is replaced by new one
    CHECK(c.has(get_tx_id(tx)));
    CHECK(c.has(txs[1].id));
    CHECK(!c.has(txs[2].id));
  }

  SECTION("invalid") {
    auto wrapped_tx = std::make_shared<::wrapped_tx>(test_helper->make_random_wrapped_tx("user"));
    auto item = c.get(wrapped_tx->id());
    CHECK(!item.has_value());
  }

  SECTION("del") {
    CHECK(c.has(txs[3].id));
    c.del(txs[3].id);
    CHECK(!c.has(txs[3].id));
    CHECK(c.size() == tx_count - 1);
  }

  SECTION("get") {
    for (auto& tx : txs) {
      auto res = c.get(tx.id);
      CHECKED_IF(res.has_value()) {
        CHECK(to_string(tx.id) == to_string(get_tx_id(res.value())));
      }
    }
  }
}
