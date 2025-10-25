//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <stdexcept>
#include <string>

class ArithmeticException final : public std::domain_error {
  public:
    explicit ArithmeticException(const std::string &message) : std::domain_error{message} {}
    ~ArithmeticException() = default;
};
