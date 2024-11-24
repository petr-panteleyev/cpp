#ifndef PASSWORD_GENERATOR_HPP
#define PASSWORD_GENERATOR_HPP

/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include <exception>
#include <string>

namespace password_generator {

const int MIN_PASSWORD_LENGTH = 4;

enum class PasswordGeneratorError {
    NO_CHARACTER_SET,
    LENGTH_TOO_SMALL,
};

class PasswordGeneratorException final : std::exception {
  private:
    PasswordGeneratorError error_code_;

  public:
    PasswordGeneratorException(PasswordGeneratorError error_code) : error_code_{error_code} {}

    PasswordGeneratorError error_code() const {
        return error_code_;
    }
};

typedef struct {
    bool use_upper_case;
    bool use_lower_case;
    bool use_digits;
    bool use_symbols;
    int  length;
} PasswordGeneratorOptions;

const PasswordGeneratorOptions PIN_OPTIONS  = {false, false, true, false, 4};
const PasswordGeneratorOptions UNIX_OPTIONS = {true, true, true, true, 8};
const PasswordGeneratorOptions MEDIUM_OPTIONS = {true, true, true, true, 16};
const PasswordGeneratorOptions LONG_OPTIONS = {true, true, true, true, 32};

std::string generate(const PasswordGeneratorOptions &options);

} // namespace password_generator

#endif
