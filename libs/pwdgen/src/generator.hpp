//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <expected>
#include <string>

namespace pwdgen {

constexpr int MIN_PASSWORD_LENGTH = 4;

enum class Error {
    NO_CHARACTER_SET,
    LENGTH_TOO_SMALL,
};

struct Options final {
    bool useUpperCase;
    bool useLowerCase;
    bool useDigits;
    bool useSymbols;
    int length;
};

constexpr Options PIN_OPTIONS = {false, false, true, false, 4};
constexpr Options UNIX_OPTIONS = {true, true, true, true, 8};
constexpr Options MEDIUM_OPTIONS = {true, true, true, true, 16};
constexpr Options LONG_OPTIONS = {true, true, true, true, 32};

auto generate(const Options &options) noexcept -> std::expected<std::string, Error>;

} // namespace pwdgen
