#pragma once
#include <cinttypes>
#include <chrono>
#include <vector>
#include <fc/crypto/sha256.hpp>
#include <fc/crypto/public_key.hpp>
#include <fc/crypto/private_key.hpp>

namespace noir::net {

using tstamp = std::chrono::system_clock::duration::rep;
using bytes = std::vector<char>;
using signature = bytes;

using block_id_type = fc::sha256;

using public_key_type = fc::crypto::public_key;
using private_key_type = fc::crypto::private_key;
using signature_type = fc::crypto::signature;

/**
 * default value initializers
 */
constexpr auto def_send_buffer_size_mb = 4;
constexpr auto def_send_buffer_size = 1024 * 1024 * def_send_buffer_size_mb;
constexpr auto def_max_write_queue_size = def_send_buffer_size * 10;
constexpr auto def_max_trx_in_progress_size = 100 * 1024 * 1024; // 100 MB
constexpr auto def_max_consecutive_immediate_connection_close = 9; // back off if client keeps closing
constexpr auto def_max_clients = 25; // 0 for unlimited clients
constexpr auto def_max_nodes_per_host = 1;
constexpr auto def_conn_retry_wait = 30;
constexpr auto def_txn_expire_wait = std::chrono::seconds(3);
constexpr auto def_resp_expected_wait = std::chrono::seconds(5);
constexpr auto def_sync_fetch_span = 100;
constexpr auto def_keepalive_interval = 32000;

constexpr auto message_header_size = 4;

}
