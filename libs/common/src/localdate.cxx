//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <chrono>

export module libs.common.localdate;

using namespace std::chrono;

export namespace LocalDate {

std::chrono::year_month_day now() {
    auto now = system_clock::now();
    auto local = current_zone()->to_local(now);
    return year_month_day{floor<days>(local)};
}

std::string toIsoString(const std::chrono::year_month_day &date) {
    return std::format("{0:%F}", date);
}

std::chrono::year_month_day fromIsoString(const std::string &str) {
    std::istringstream input{str};
    year_month_day result;
    input >> parse("%F", result);
    return result;
}

} // namespace LocalDate
