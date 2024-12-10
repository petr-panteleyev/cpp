/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CREDITCARDTYPE_H
#define CREDITCARDTYPE_H

#include "picture.h"
#include <QString>
#include <functional>
#include <vector>

class CreditCardType;
using CreditCardTypeRef = std::reference_wrapper<const CreditCardType>;

class CreditCardType {
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
    static const CreditCardType                 &valueOf(const std::string &name);
    static const CreditCardType                 &valueOf(unsigned ordinal) { return values_.at(ordinal); }
    static const std::vector<CreditCardTypeRef> &values() noexcept { return values_; }

    unsigned           ordinal() const noexcept { return ordinal_; }
    const std::string &name() const noexcept { return name_; }
    const QString     &cardTypeName() const noexcept { return cardTypeName_; }
    const Picture     &picture() const noexcept { return picture_; }

  private:
    CreditCardType(unsigned ordinal, const std::string &name, const QString &cardTypeName, const Picture &picture)
        : ordinal_{ordinal}, name_{name}, cardTypeName_{cardTypeName}, picture_{picture} {}

    CreditCardType(const CreditCardType &) = delete;
    CreditCardType(const CreditCardType &&) = delete;

  private:
    unsigned       ordinal_;
    std::string    name_;
    QString        cardTypeName_;
    const Picture &picture_;

    const static std::vector<CreditCardTypeRef> values_;
};

#endif // CREDITCARDTYPE_H
