//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <string>

class PasswordManagerException : std::exception {
  public:
    PasswordManagerException(const std::u16string &message) : message_{message} {}

    const std::u16string &message() const noexcept { return message_; }

  private:
    std::u16string message_;
};
