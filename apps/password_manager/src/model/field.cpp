//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "field.h"
#include "creditcardtype.h"
#include "fieldtype.h"
#include <QDate>

static QDate parseLocalDate(const QString &stringValue);

Field::Field(const FieldType &type, const QString &name, const QVariant &value) noexcept
    : type_{type}, name_{name}, value_{value}, showContent_{!type.masked()} {
}

void Field::toggleShow() noexcept {
    if (type().masked()) {
        showContent_ = !showContent_;
    }
}

QString Field::getValueAsString() const {
    if (type_ == FieldType::DATE) {
        auto date = value_.toDate();
        return date.toString("dd.MM.yyyy");
    } else if (type_ == FieldType::EXPIRATION_MONTH) {
        auto date = value_.toDate();
        return date.toString("MM/yy");
    } else if (type_ == FieldType::CARD_TYPE) {
        auto ordinal = value_.toUInt();
        const CreditCardType &creditCardType = CreditCardType::valueOf(ordinal);
        return creditCardType.cardTypeName();
    } else {
        return value_.toString();
    }
}

QVariant Field::deserialize(const QString &str, const FieldType &type) {
    QVariant value;
    if (type == FieldType::CARD_TYPE) {
        value = CreditCardType::valueOf(str.toStdString()).ordinal();
    } else if (type == FieldType::DATE || type == FieldType::EXPIRATION_MONTH) {
        value = parseLocalDate(str);
    } else {
        value = str;
    }
    return value;
}

QVariant Field::convertValue(const FieldType &type) const noexcept {
    if (type == FieldType::DATE || type == FieldType::EXPIRATION_MONTH) {
        return QDate::currentDate();
    } else if (type == FieldType::CARD_TYPE) {
        return CreditCardType::MIR.ordinal();
    } else {
        return getValueAsString();
    }
}

static QDate parseLocalDate(const QString &stringValue) {
    if (stringValue.isEmpty()) {
        return QDate::currentDate();
    }
    auto date = QDate::fromString(stringValue, "yyyy-MM-dd");
    return date.isValid() ? date : QDate::currentDate();
}
