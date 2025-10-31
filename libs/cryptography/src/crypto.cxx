//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <exception>
#include <span>
#include <string>
#include <vector>

export module libs.cryptography;

export namespace Crypto {

class CryptoException : public std::exception {
  public:
    explicit CryptoException(const std::string &message) noexcept : message_{message} {}

    const std::string &message() const noexcept { return message_; }

  private:
    const std::string message_;
};

} // namespace Crypto

export namespace Crypto::aes256 {

std::vector<char> decrypt(const std::span<char> &encrypted, const std::string &passwd);
std::vector<char> encrypt(const std::span<char> &decrypted, const std::string &passwd);

} // namespace Crypto::aes256
