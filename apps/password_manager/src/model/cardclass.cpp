/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardclass.h"
#include <map>
#include <stdexcept>
#include <functional>

using CardClassRef = std::reference_wrapper<const CardClass>;

static const std::map<CardClassEnum, CardClassRef> CARD_CLASS_ENUMS{
    {CardClassEnum::CARD, std::cref(CardClass::CARD)},
    {CardClassEnum::NOTE, std::cref(CardClass::NOTE)}
};

const CardClass &CardClass::valueOf(const std::string &name) {
    for (const auto &entry : CARD_CLASS_ENUMS) {
        if (entry.second.get().name() == name) {
            return entry.second;
        }
    }
    throw std::out_of_range("CardClass::" + name + " is not defined");
}

const CardClass &CardClass::valueOf(CardClassEnum value) {
    return CARD_CLASS_ENUMS.at(value);
}
