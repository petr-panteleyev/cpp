//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <boost/decimal.hpp>
#include <format>
#include <string>

namespace Numeric {

using Decimal = boost::decimal::decimal128_t;

constexpr auto DECIMAL_ZERO = boost::decimal::decimal128_t{0};
constexpr auto DECIMAL_ONE = boost::decimal::decimal128_t{1};
constexpr auto DECIMAL_TEN = boost::decimal::decimal128_t{10};

inline auto toFinancialString2(const Decimal &value) noexcept -> std::string {
    return std::format("{:.2f}", value);
}

inline auto toFinancialString6(const Decimal &value) noexcept -> std::string {
    return std::format("{:.6f}", value);
}

} // namespace Numeric
