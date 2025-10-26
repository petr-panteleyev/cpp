//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <chrono>

namespace LocalDate {

std::chrono::year_month_day now();
std::string toIsoString(const std::chrono::year_month_day &date);
std::chrono::year_month_day fromIsoString(const std::string &str);

} // namespace LocalDate
