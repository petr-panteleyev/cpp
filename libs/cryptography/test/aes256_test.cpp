//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include <gtest/gtest.h>
#include <string>

import libs.cryptography;

namespace {

struct Aes256TestParams {
    std::string string_;
    std::string password_;
};

class Aes256Test : public ::testing::TestWithParam<Aes256TestParams> {};

} // namespace

INSTANTIATE_TEST_SUITE_P(Crypto, Aes256Test,
                         ::testing::Values(Aes256TestParams{"", ""}, Aes256TestParams{"", "test password"},
                                           Aes256TestParams{"test string", "test password"},
                                           Aes256TestParams{"test string", ""}));

TEST_P(Aes256Test, encrypt_decrypt) {
    auto [str, password] = GetParam();
    std::vector bytes(str.begin(), str.end());

    auto encrypted = Crypto::aes256::encrypt(bytes, password);
    auto decrypted = Crypto::aes256::decrypt(encrypted, password);

    EXPECT_EQ(decrypted, bytes);
}
