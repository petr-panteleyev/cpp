//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "generator.hpp"
#include <gtest/gtest.h>

TEST(PwdGenTestSuite, OptionsLong) {
    auto password = pwdgen::generate(pwdgen::LONG_OPTIONS).value();
    EXPECT_EQ(pwdgen::LONG_OPTIONS.length, password.length());
}

TEST(PwdGenTestSuite, OptionsMedium) {
    auto password = pwdgen::generate(pwdgen::MEDIUM_OPTIONS).value();
    EXPECT_EQ(pwdgen::MEDIUM_OPTIONS.length, password.length());
}
TEST(PwdGenTestSuite, OptionsPIN) {
    auto password = pwdgen::generate(pwdgen::PIN_OPTIONS).value();
    EXPECT_EQ(pwdgen::PIN_OPTIONS.length, password.length());
}
TEST(PwdGenTestSuite, OptionsUNIX) {
    auto password = pwdgen::generate(pwdgen::UNIX_OPTIONS).value();
    EXPECT_EQ(pwdgen::UNIX_OPTIONS.length, password.length());
}
