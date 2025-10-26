//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include <chrono>
#include <gtest/gtest.h>

import libs.common.localdate;

using namespace std::chrono;

namespace {

struct IsoStringTestParams {
    std::chrono::year_month_day date_;
    std::string string_;
};

class IsoStringTest : public ::testing::TestWithParam<IsoStringTestParams> {};

} // namespace

INSTANTIATE_TEST_SUITE_P(
    LocalDate, IsoStringTest,
    ::testing::Values(IsoStringTestParams{year_month_day{year{2025}, month{1}, day{2}}, "2025-01-02"},
                      IsoStringTestParams{year_month_day{year{2025}, month{1}, day{12}}, "2025-01-12"},
                      IsoStringTestParams{year_month_day{year{2025}, month{10}, day{1}}, "2025-10-01"},
                      IsoStringTestParams{year_month_day{year{2025}, month{10}, day{12}}, "2025-10-12"}));

TEST_P(IsoStringTest, toIsoString) {
    auto [date, expected] = GetParam();
    auto actual = LocalDate::toIsoString(date);
    EXPECT_EQ(actual, expected);
}

TEST_P(IsoStringTest, fromIsoString) {
    auto [expected, str] = GetParam();
    auto actual = LocalDate::fromIsoString(str);
    EXPECT_EQ(actual, expected);
}
