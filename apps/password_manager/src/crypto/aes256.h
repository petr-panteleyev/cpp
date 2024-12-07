/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef AES256_H
#define AES256_H

#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <QByteArray>

namespace aes256 {

using BufferPtr = std::shared_ptr<unsigned char[]>;
using DecryptionResult = std::pair<BufferPtr, int>;

class DecryptionException : public std::exception {};

DecryptionResult decrypt(const QByteArray &encrypted, const std::string &passwd);

} // namespace aes256

#endif // AES256_H
