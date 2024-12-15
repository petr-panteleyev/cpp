/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef AES256_H
#define AES256_H

#include "cryptoexception.h"
#include <span>
#include <string>
#include <vector>

namespace Crypto::aes256 {

std::vector<char> decrypt(const std::span<char> &encrypted, const std::string &passwd);
std::vector<char> encrypt(const std::span<char> &decrypted, const std::string &passwd);

} // namespace Crypto::aes256

#endif // AES256_H
