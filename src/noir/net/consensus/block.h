#pragma once
#include <noir/net/protocol.h>

namespace noir::net::consensus { // todo - where to place?

struct block {
  //mutex mtx;
  //header header;
  //data data;
  //evidence evidence;
  //commit last_commit;
};

struct vote_extension_to_sign {
  bytes add_data_to_sign;
};

struct commit_sig {
  std::byte block_id_flag;
  bytes validator_address;
  tstamp timestamp;
  bytes signature;
  vote_extension_to_sign vote_extension;
};

struct commit {
  int64_t height;
  int32_t round;
  block_id block_id;
  std::vector<commit_sig> signatures;

  //hash // todo - do we need these?
  //bitArray
};

using block_ptr = std::shared_ptr<block>;

}
