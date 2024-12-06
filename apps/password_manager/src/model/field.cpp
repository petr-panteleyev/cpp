/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "field.h"
#include <QDate>
#include "creditcardtype.h"

static QDate parseLocalDate(const QString &stringValue);

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

static QDate parseLocalDate(const QString &stringValue) {
    if (stringValue.isEmpty()) {
        return QDate::currentDate();
    }
    auto date = QDate::fromString(stringValue, "yyyy-MM-dd");
    return date.isValid() ? date : QDate::currentDate();
}

