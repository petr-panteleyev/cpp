/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "generator.h"
#include "character_set.h"
#include <algorithm>
#include <random>
#include <vector>

namespace password_generator {

using Charsets = std::vector<const CharacterSet *>;

static int  random_number(int max_value);
static bool password_is_ok(const Charsets &charsets, const std::string &password);

static std::random_device rd;
static std::mt19937       rand(rd());

std::string generate(const PasswordGeneratorOptions &options) {
    if (options.length < MIN_PASSWORD_LENGTH) {
        throw PasswordGeneratorException(PasswordGeneratorError::LENGTH_TOO_SMALL);
    }

    Charsets used_charsets;

    if (options.use_upper_case) {
        used_charsets.push_back(&CharacterSet::UPPER_CASE_CHARS);
    }
    if (options.use_lower_case) {
        used_charsets.push_back(&CharacterSet::LOWER_CASE_CHARS);
    }
    if (options.use_digits) {
        used_charsets.push_back(&CharacterSet::DIGITS);
    }
    if (options.use_symbols) {
        used_charsets.push_back(&CharacterSet::SYMBOLS);
    }
    if (used_charsets.empty()) {
        throw PasswordGeneratorException(PasswordGeneratorError::NO_CHARACTER_SET);
    }

    std::string password;

    while (true) {
        for (auto i = 0; i < options.length; i++) {
            auto random_charset = used_charsets[random_number(used_charsets.size())];

            char random_char;
            do {
                random_char = random_charset->at(random_number(random_charset->size()));
            } while (CharacterSet::BAD_LETTERS.contains(random_char));

            password += random_char;
        }

        if (password_is_ok(used_charsets, password)) {
            return password;
        } else {
            password.clear();
        }
    }
}

static int random_number(int max_value) {
    return rand() % max_value;
}

static bool password_is_ok(const Charsets &charsets, const std::string &password) {
    return std::find_if(charsets.begin(), charsets.end(),
                        [password](auto charset) { return !charset->contains_any(password); }) == charsets.end();
}

} // namespace password_generator
