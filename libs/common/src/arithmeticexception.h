//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ARITHMETICEXCEPTION_H
#define ARITHMETICEXCEPTION_H

#include <stdexcept>
#include <string>

class ArithmeticException final : public std::domain_error {
  public:
    explicit ArithmeticException(const std::string &message) : std::domain_error{message} {}
    ~ArithmeticException() = default;
};

#endif // ARITHMETICEXCEPTION_H
