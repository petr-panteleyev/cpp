//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>

class PasswordManagerException : std::exception {
  public:
    PasswordManagerException(const QString &message) : message_{message} {}

    const QString &message() const noexcept { return message_; }

  private:
    QString message_;
};

#endif // EXCEPTIONS_H
