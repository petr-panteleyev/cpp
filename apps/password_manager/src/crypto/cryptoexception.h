//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CRYPTOEXCEPTION_H
#define CRYPTOEXCEPTION_H

namespace Crypto {

class CryptoException : public std::exception {
  public:
    explicit CryptoException(const std::string &message) noexcept : message_{message} {}

    const std::string &message() const noexcept { return message_; }

  private:
    const std::string message_;
};

} // namespace Crypto

#endif // CRYPTOEXCEPTION_H
