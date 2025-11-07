//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <chrono>

namespace LocalDate {

inline std::chrono::year_month_day now() {
    auto now = std::chrono::system_clock::now();
    auto local = std::chrono::current_zone()->to_local(now);
    return std::chrono::year_month_day{floor<std::chrono::days>(local)};
}

inline std::string toIsoString(const std::chrono::year_month_day &date) {
    return std::format("{0:%F}", date);
}

inline std::chrono::year_month_day fromIsoString(const std::string &str) {
    std::istringstream input{str};
    std::chrono::year_month_day result;
    input >> parse("%F", result);
    return result;
}

} // namespace LocalDate
