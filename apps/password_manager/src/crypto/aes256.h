/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef AES256_H
#define AES256_H

#include <QByteArray>
#include <QString>
#include <exception>

namespace aes256 {

class DecryptionException : public std::exception {
  public:
    DecryptionException(const std::string &message) : message_{message} {}

    const std::string &message() const noexcept { return message_; }

  private:
    const std::string message_;
};

void decrypt(const QByteArray &encrypted, const QString &passwd, QByteArray &decrypted);

} // namespace aes256

#endif // AES256_H
