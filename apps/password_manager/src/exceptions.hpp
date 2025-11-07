//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QString>

class PasswordManagerException : std::exception {
  public:
    PasswordManagerException(const QString &message) : message_{message} {}

    const QString &message() const noexcept { return message_; }

  private:
    QString message_;
};
