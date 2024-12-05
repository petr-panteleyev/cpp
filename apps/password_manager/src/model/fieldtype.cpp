/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "fieldtype.h"
#include <functional>
#include <map>
#include <stdexcept>

using FieldTypeRef = std::reference_wrapper<const FieldType>;

const FieldType FieldType::STRING{FieldTypeEnum::STRING, "STRING"};
const FieldType FieldType::HIDDEN{FieldTypeEnum::HIDDEN, "HIDDEN", true};
const FieldType FieldType::EMAIL{FieldTypeEnum::EMAIL, "EMAIL"};
const FieldType FieldType::CREDIT_CARD_NUMBER{FieldTypeEnum::CREDIT_CARD_NUMBER, "CREDIT_CARD_NUMBER"};
const FieldType FieldType::LINK{FieldTypeEnum::LINK, "LINK"};
const FieldType FieldType::PIN{FieldTypeEnum::PIN, "PIN", true};
const FieldType FieldType::UNIX_PASSWORD{FieldTypeEnum::UNIX_PASSWORD, "UNIX_PASSWORD", true};
const FieldType FieldType::SHORT_PASSWORD{FieldTypeEnum::SHORT_PASSWORD, "SHORT_PASSWORD", true};
const FieldType FieldType::LONG_PASSWORD{FieldTypeEnum::LONG_PASSWORD, "LONG_PASSWORD", true};
const FieldType FieldType::CARD_TYPE{FieldTypeEnum::CARD_TYPE, "CARD_TYPE"};
const FieldType FieldType::DATE{FieldTypeEnum::DATE, "DATE"};
const FieldType FieldType::EXPIRATION_MONTH{FieldTypeEnum::EXPIRATION_MONTH, "EXPIRATION_MONTH"};

static const std::map<FieldTypeEnum, FieldTypeRef> FIELD_TYPE_ENUMS{
    {FieldTypeEnum::STRING, std::cref(FieldType::STRING)},
    {FieldTypeEnum::HIDDEN, std::cref(FieldType::HIDDEN)},
    {FieldTypeEnum::EMAIL, std::cref(FieldType::EMAIL)},
    {FieldTypeEnum::CREDIT_CARD_NUMBER, std::cref(FieldType::CREDIT_CARD_NUMBER)},
    {FieldTypeEnum::LINK, std::cref(FieldType::LINK)},
    {FieldTypeEnum::PIN, std::cref(FieldType::PIN)},
    {FieldTypeEnum::UNIX_PASSWORD, std::cref(FieldType::UNIX_PASSWORD)},
    {FieldTypeEnum::SHORT_PASSWORD, std::cref(FieldType::SHORT_PASSWORD)},
    {FieldTypeEnum::LONG_PASSWORD, std::cref(FieldType::LONG_PASSWORD)},
    {FieldTypeEnum::CARD_TYPE, std::cref(FieldType::CARD_TYPE)},
    {FieldTypeEnum::DATE, std::cref(FieldType::DATE)},
    {FieldTypeEnum::EXPIRATION_MONTH, std::cref(FieldType::EXPIRATION_MONTH)},
};

const FieldType &FieldType::valueOf(const std::string &name) {
    for (const auto &entry : FIELD_TYPE_ENUMS) {
        if (entry.second.get().name_ == name) {
            return entry.second;
        }
    }
    throw std::out_of_range("FieldType::" + name + " not defined");
}

const FieldType &FieldType::valueOf(FieldTypeEnum value) {
    return FIELD_TYPE_ENUMS.at(value);
}
