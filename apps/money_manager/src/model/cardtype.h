//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDTYPE_H
#define CARDTYPE_H

#include "enumclass.h"
#include <functional>

class CardType : public Common::EnumClass<CardType> {
  public:
    static const CardType NONE;
    static const CardType VISA;
    static const CardType MASTERCARD;
    static const CardType MIR;
    static const CardType AMEX;

  public:
    ~CardType() = default;

  private:
    explicit CardType(const std::string &name) : EnumClass{name} {}
};

using CardTypeRef = std::reference_wrapper<const CardType>;

const inline CardType CardType::NONE{"NONE"};
const inline CardType CardType::VISA{"VISA"};
const inline CardType CardType::MASTERCARD{"MASTERCARD"};
const inline CardType CardType::MIR{"MIR"};
const inline CardType CardType::AMEX{"AMEX"};

template <>
const inline std::vector<CardTypeRef> Common::EnumClass<CardType>::values_{
    std::cref(CardType::NONE), std::cref(CardType::VISA), std::cref(CardType::MASTERCARD),
    std::cref(CardType::MIR),  std::cref(CardType::AMEX),
};

#endif // CARDTYPE_H
