//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "qthelpers.hpp"
#include <QDate>
#include <gtest/gtest.h>

namespace {

struct ChronoAndQDateTestParams {
    std::chrono::year_month_day ymd_;
    QDate qdate_;
};

class QDateToChronoTest : public ::testing::TestWithParam<ChronoAndQDateTestParams> {};

} // namespace

INSTANTIATE_TEST_SUITE_P(QtHelpers, QDateToChronoTest,
                         ::testing::Values(ChronoAndQDateTestParams{std::chrono::year_month_day{}, QDate{}},
                                           ChronoAndQDateTestParams{std::chrono::year_month_day{
                                                                        std::chrono::year{2025},
                                                                        std::chrono::month{10},
                                                                        std::chrono::day{3},
                                                                    },
                                                                    QDate{2025, 10, 3}},
                                           ChronoAndQDateTestParams{std::chrono::year_month_day{},
                                                                    QDate{2025, 13, 3}}));

TEST_P(QDateToChronoTest, ) {
    auto [expected, given] = GetParam();
    auto actual = QtHelpers::toChrono(given);
    EXPECT_EQ(actual, expected);
}
