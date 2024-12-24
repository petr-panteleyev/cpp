//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "characterset.h"
#include <algorithm>

namespace pwdgen {

const CharacterSet CharacterSet::UPPER_CASE_CHARS{{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                                   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};

const CharacterSet CharacterSet::LOWER_CASE_CHARS{{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                                   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}};

const CharacterSet CharacterSet::DIGITS{{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}};

const CharacterSet CharacterSet::SYMBOLS{{'@', '#', '$', '%', '&', '*', '(', ')', '-', '+', '=', '^', '.', ','}};

const CharacterSet CharacterSet::BAD_LETTERS{{'I', 'l', 'O'}};

bool CharacterSet::contains(char ch) const {
    return std::find(characters_.begin(), characters_.end(), ch) != characters_.end();
}

bool CharacterSet::containsAny(const std::string &str) const {
    return std::find_if(str.begin(), str.end(), [this](auto ch) { return this->contains(ch); }) != str.end();
}

} // namespace pwdgen
