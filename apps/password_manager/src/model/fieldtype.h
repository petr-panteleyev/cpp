/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef FIELDTYPE_H
#define FIELDTYPE_H

#include "enumclass.h"
#include <functional>
#include <string>

class FieldType;
using FieldTypeRef = std::reference_wrapper<const FieldType>;

class FieldType final : public EnumClass<FieldType> {
  public:
    static const FieldType STRING;
    static const FieldType HIDDEN;
    static const FieldType EMAIL;
    static const FieldType CREDIT_CARD_NUMBER;
    static const FieldType LINK;
    static const FieldType PIN;
    static const FieldType UNIX_PASSWORD;
    static const FieldType SHORT_PASSWORD;
    static const FieldType LONG_PASSWORD;
    static const FieldType CARD_TYPE;
    static const FieldType DATE;
    static const FieldType EXPIRATION_MONTH;

  public:
    bool masked() const { return masked_; }

  private:
    FieldType(const std::string &name) : EnumClass{name}, masked_{false} {}
    FieldType(const std::string &name, bool masked) : EnumClass{name}, masked_{masked} {}

  private:
    const bool masked_;
};

#endif // FIELDTYPE_H
