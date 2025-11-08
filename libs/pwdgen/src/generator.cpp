//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "generator.hpp"
#include "characterset.hpp"
#include <algorithm>
#include <random>
#include <vector>

namespace {

using Charsets = std::vector<const pwdgen::CharacterSet *>;

std::random_device rd;
std::mt19937 rand(rd());

auto randomNumber(int max_value) -> int {
    return rand() % max_value;
}

auto passwordIsOk(const Charsets &charsets, const std::string &password) -> bool {
    return std::find_if(charsets.begin(), charsets.end(),
                        [password](auto charset) { return !charset->containsAny(password); }) == charsets.end();
}

} // namespace

namespace pwdgen {

auto generate(const Options &options) noexcept -> std::expected<std::string, Error> {
    if (options.length < MIN_PASSWORD_LENGTH) {
        return std::unexpected(Error::LENGTH_TOO_SMALL);
    }

    Charsets usedCharsets;

    if (options.useUpperCase) {
        usedCharsets.push_back(&CharacterSet::UPPER_CASE_CHARS);
    }
    if (options.useLowerCase) {
        usedCharsets.push_back(&CharacterSet::LOWER_CASE_CHARS);
    }
    if (options.useDigits) {
        usedCharsets.push_back(&CharacterSet::DIGITS);
    }
    if (options.useSymbols) {
        usedCharsets.push_back(&CharacterSet::SYMBOLS);
    }
    if (usedCharsets.empty()) {
        return std::unexpected(Error::NO_CHARACTER_SET);
    }

    std::string password;

    while (true) {
        for (auto i = 0; i < options.length; i++) {
            auto randomCharset = usedCharsets[randomNumber(usedCharsets.size())];

            char randomChar;
            do {
                randomChar = randomCharset->at(randomNumber(randomCharset->size()));
            } while (CharacterSet::BAD_LETTERS.contains(randomChar));

            password += randomChar;
        }

        if (passwordIsOk(usedCharsets, password)) {
            return password;
        } else {
            password.clear();
        }
    }
}

} // namespace pwdgen
