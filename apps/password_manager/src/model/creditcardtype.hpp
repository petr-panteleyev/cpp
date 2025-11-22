//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "enumclass.hpp"

class Picture;

class CreditCardType final : public Common::EnumClass<CreditCardType> {
  public:
    static const CreditCardType AMEX;
    static const CreditCardType DINERS;
    static const CreditCardType JCB;
    static const CreditCardType MASTERCARD;
    static const CreditCardType MIR;
    static const CreditCardType PAYPAL;
    static const CreditCardType UNION_PAY;
    static const CreditCardType VISA;
    static const CreditCardType OTHER;

  public:
    const std::u16string &cardTypeName() const noexcept { return cardTypeName_; }
    const Picture &picture() const noexcept { return picture_; }

  private:
    explicit CreditCardType(const std::string &name, const std::u16string &cardTypeName,
                            const Picture &picture) noexcept
        : EnumClass{name}, cardTypeName_{cardTypeName}, picture_{picture} {}

  private:
    std::u16string cardTypeName_;
    const Picture &picture_;
};
