//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "numeric.hpp"
#include <gtest/gtest.h>

using namespace Numeric;

namespace {

struct StringTestParam {
    Decimal decimal_;
    std::string string_;
};

class Financial2Test : public ::testing::TestWithParam<StringTestParam> {};
class Financial6Test : public ::testing::TestWithParam<StringTestParam> {};

} // namespace

INSTANTIATE_TEST_SUITE_P(Decimal, Financial2Test,
                         ::testing::Values(StringTestParam{.decimal_ = Decimal{1234, -3}, .string_ = "1.23"},
                                           StringTestParam{.decimal_ = Decimal{-1234, -3}, .string_ = "-1.23"},
                                           StringTestParam{.decimal_ = Decimal{1235, -3}, .string_ = "1.24"},
                                           StringTestParam{.decimal_ = Decimal{-1235, -3}, .string_ = "-1.24"},
                                           StringTestParam{.decimal_ = Decimal{1200, -3}, .string_ = "1.20"}));

TEST_P(Financial2Test, ) {
    auto [x, expected] = GetParam();
    auto actual = Numeric::toFinancialString2(x);
    EXPECT_EQ(actual, expected);
}

INSTANTIATE_TEST_SUITE_P(Decimal, Financial6Test,
                         ::testing::Values(StringTestParam{.decimal_ = Decimal{1234, -3}, .string_ = "1.234000"},
                                           StringTestParam{.decimal_ = Decimal{-1234, -3}, .string_ = "-1.234000"},
                                           StringTestParam{.decimal_ = Decimal{1235, -3}, .string_ = "1.235000"},
                                           StringTestParam{.decimal_ = Decimal{-1235, -3}, .string_ = "-1.235000"}));

TEST_P(Financial6Test, ) {
    auto [x, expected] = GetParam();
    auto actual = Numeric::toFinancialString6(x);
    EXPECT_EQ(actual, expected);
}
