//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <stdexcept>

class SqlException final : public std::runtime_error {
  public:
    explicit SqlException(const std::string &message) : std::runtime_error{message} {}
};
