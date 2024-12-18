/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <exception>
#include <string>

namespace pwdgen {

constexpr int MIN_PASSWORD_LENGTH = 4;

enum class PasswordGeneratorError {
    NO_CHARACTER_SET,
    LENGTH_TOO_SMALL,
};

class PasswordGeneratorException final : std::exception {
  private:
    PasswordGeneratorError errorCode_;

  public:
    explicit PasswordGeneratorException(PasswordGeneratorError errorCode) : errorCode_{errorCode} {}

    PasswordGeneratorError errorCode() const { return errorCode_; }
};

typedef struct {
    bool useUpperCase;
    bool useLowerCase;
    bool useDigits;
    bool useSymbols;
    int  length;
} PasswordGeneratorOptions;

constexpr PasswordGeneratorOptions PIN_OPTIONS = {false, false, true, false, 4};
constexpr PasswordGeneratorOptions UNIX_OPTIONS = {true, true, true, true, 8};
constexpr PasswordGeneratorOptions MEDIUM_OPTIONS = {true, true, true, true, 16};
constexpr PasswordGeneratorOptions LONG_OPTIONS = {true, true, true, true, 32};

std::string generate(const PasswordGeneratorOptions &options);

} // namespace pwdgen

#endif
