//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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
