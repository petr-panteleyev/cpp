//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "generator.hpp"
#include "characterset.hpp"
#include <algorithm>
#include <random>
#include <vector>

namespace pwdgen {

using Charsets = std::vector<const CharacterSet *>;

static std::random_device rd;
static std::mt19937 rand(rd());

static int randomNumber(int max_value) {
    return rand() % max_value;
}

static bool passwordIsOk(const Charsets &charsets, const std::string &password) {
    return std::find_if(charsets.begin(), charsets.end(),
                        [password](auto charset) { return !charset->containsAny(password); }) == charsets.end();
}

std::string generate(const PasswordGeneratorOptions &options) {
    if (options.length < MIN_PASSWORD_LENGTH) {
        throw PasswordGeneratorException(PasswordGeneratorError::LENGTH_TOO_SMALL);
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
        throw PasswordGeneratorException(PasswordGeneratorError::NO_CHARACTER_SET);
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
