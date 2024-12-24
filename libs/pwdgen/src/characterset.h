//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CHARACTERSET_H
#define CHARACTERSET_H

#include <string>
#include <vector>

namespace pwdgen {

class CharacterSet final {
  public:
    static const CharacterSet UPPER_CASE_CHARS;
    static const CharacterSet LOWER_CASE_CHARS;
    static const CharacterSet DIGITS;
    static const CharacterSet SYMBOLS;
    static const CharacterSet BAD_LETTERS;

    char at(std::size_t index) const {
        return characters_.at(index);
    }

    std::size_t size() const {
        return characters_.size();
    }

    // Returns true if character set contains given character.
    bool contains(char ch) const;

    // Returns true if character set contains any character from a given string.
    bool containsAny(const std::string &str) const;

  private:
    const std::vector<char> characters_;

    explicit CharacterSet(const std::vector<char> &characters) : characters_(characters) {
    }
};

} // namespace password_generator

#endif
