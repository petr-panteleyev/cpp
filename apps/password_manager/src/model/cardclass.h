//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDCLASS_H
#define CARDCLASS_H

#include "enumclass.h"
#include <functional>

class CardClass final : public Common::EnumClass<CardClass> {
  public:
    static const CardClass CARD;
    static const CardClass NOTE;

  private:
    explicit CardClass(const std::string &name) noexcept : EnumClass{name} {}
};

using CardClassRef = std::reference_wrapper<const CardClass>;

const inline CardClass CardClass::CARD{"CARD"};
const inline CardClass CardClass::NOTE{"NOTE"};

template <>
const inline std::vector<CardClassRef> Common::EnumClass<CardClass>::values_{
    std::cref(CardClass::CARD),
    std::cref(CardClass::NOTE),
};

#endif // CARDCLASS_H
