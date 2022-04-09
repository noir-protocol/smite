// This file is part of NOIR.
//
// Copyright (c) 2022 Haderech Pte. Ltd.
// SPDX-License-Identifier: AGPL-3.0-or-later
//
#include <noir/common/check.h>
#include <noir/crypto/hash.h>

extern "C" {
#include <KeccakHash.h>
}

namespace noir::crypto {

namespace unsafe {
  void sha3_256(std::span<const char> in, std::span<char> out) {
    Keccak_HashInstance ctx;
    Keccak_HashInitialize_SHA3_256(&ctx);
    Keccak_HashUpdate(&ctx, (BitSequence*)in.data(), in.size() * 8);
    Keccak_HashFinal(&ctx, (BitSequence*)out.data());
  }
} // namespace unsafe

/// \cond PRIVATE
struct sha3_256::sha3_256_impl : public hash {
  hash& init() override {
    Keccak_HashInitialize_SHA3_256(&ctx);
    return *this;
  };

  hash& update(std::span<const char> in) override {
    Keccak_HashUpdate(&ctx, (BitSequence*)in.data(), in.size() * 8);
    return *this;
  }

  void final(std::span<char> out) override {
    Keccak_HashFinal(&ctx, (BitSequence*)out.data());
  }

  size_t digest_size() override {
    return 32;
  }

private:
  Keccak_HashInstance ctx;
};

/// \endcond

} // namespace noir::crypto

NOIR_CRYPTO_HASH(sha3_256);
