//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "ui_tools.hpp"
#include "creditcardtype.hpp"
#include "localdate.hpp"

namespace {

constexpr std::string YMD_FORMAT{"{0:%d.%m.%Y}"};
constexpr std::string MY_FORMAT{"{0:%m/%y}"};

} // namespace

namespace UiTools {

QString toString(const Field &field) noexcept {
    auto &type = field.type();
    auto &value = field.value();

    if (type == FieldType::DATE) {
        auto &date = std::get<std::chrono::year_month_day>(value);
        return QString::fromStdString(std::format(YMD_FORMAT, date));
    } else if (type == FieldType::EXPIRATION_MONTH) {
        auto &date = std::get<std::chrono::year_month_day>(value);
        return QString::fromStdString(std::format(MY_FORMAT, date));
    } else if (type == FieldType::CARD_TYPE) {
        auto ordinal = std::get<unsigned int>(value);
        auto &creditCardType = CreditCardType::valueOf(ordinal);
        return QString(creditCardType.cardTypeName());
    } else {
        return QString(std::get<std::u16string>(value));
    }
}

Field::FieldValue convertValue(const Field &field, const FieldType &newType) noexcept {
    if (newType == FieldType::DATE || newType == FieldType::EXPIRATION_MONTH) {
        return LocalDate::now();
    } else if (newType == FieldType::CARD_TYPE) {
        return CreditCardType::MIR.ordinal();
    } else {
        return toString(field).toStdU16String();
    }
}

} // namespace UiTools
