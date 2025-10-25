//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <span>
#include <string>
#include <vector>

namespace Crypto::aes256 {

std::vector<char> decrypt(const std::span<char> &encrypted, const std::string &passwd);
std::vector<char> encrypt(const std::span<char> &decrypted, const std::string &passwd);

} // namespace Crypto::aes256
