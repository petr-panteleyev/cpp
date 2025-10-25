//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "characterset.h"
#include <gtest/gtest.h>

using namespace pwdgen;

static void testContains(const CharacterSet &charset) {
    for (auto i = 0; i < charset.size(); ++i) {
        EXPECT_TRUE(charset.contains(charset.at(i)));
    }
}

TEST(PwdGenCharsetTestSuite, contains_UPPER_CASE_CHARS) {
    testContains(CharacterSet::UPPER_CASE_CHARS);
}

TEST(PwdGenCharsetTestSuite, contains_LOWER_CASE_CHARS) {
    testContains(CharacterSet::LOWER_CASE_CHARS);
}

TEST(PwdGenCharsetTestSuite, contains_DIGITS) {
    testContains(CharacterSet::DIGITS);
}

TEST(PwdGenCharsetTestSuite, contains_SYMBOLS) {
    testContains(CharacterSet::SYMBOLS);
}

static void testContainsAny(const CharacterSet &charset, const std::string &password) {
    EXPECT_TRUE(charset.containsAny(password));
}

TEST(PwdGenCharsetTestSuite, containsAny_UPPER_CASE_CHARS) {
    testContainsAny(CharacterSet::UPPER_CASE_CHARS, "A123");
}

TEST(PwdGenCharsetTestSuite, containsAny_LOWER_CASE_CHARS) {
    testContainsAny(CharacterSet::LOWER_CASE_CHARS, "a123");
}

TEST(PwdGenCharsetTestSuite, containsAny_DIGITS) {
    testContainsAny(CharacterSet::DIGITS, "a123");
}

TEST(PwdGenCharsetTestSuite, containsAny_SYMBOLS) {
    testContainsAny(CharacterSet::SYMBOLS, ",.123");
}
