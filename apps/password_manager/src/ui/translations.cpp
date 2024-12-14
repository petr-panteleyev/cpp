/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "translations.h"
#include <QApplication>

std::unordered_map<unsigned, QString> Translations::fieldTypeTranslated_;
std::unordered_map<unsigned, QString> Translations::recordTypeTranslated_;

void Translations::initialize() {
    fieldTypeTranslated_ = {
        {FieldType::STRING.ordinal(), tr("String")},
        {FieldType::HIDDEN.ordinal(), tr("Hidden String")},
        {FieldType::EMAIL.ordinal(), tr("E-mail")},
        {FieldType::CREDIT_CARD_NUMBER.ordinal(), tr("Credit Card Number")},
        {FieldType::LINK.ordinal(), tr("Web Link")},
        {FieldType::PIN.ordinal(), tr("PIN code")},
        {FieldType::UNIX_PASSWORD.ordinal(), tr("UNIX password")},
        {FieldType::SHORT_PASSWORD.ordinal(), tr("Short password")},
        {FieldType::LONG_PASSWORD.ordinal(), tr("Long password")},
        {FieldType::CARD_TYPE.ordinal(), tr("Card type")},
        {FieldType::DATE.ordinal(), tr("Date")},
        {FieldType::EXPIRATION_MONTH.ordinal(), tr("Expiration Month")},
    };

    recordTypeTranslated_ = {
        {RecordType::EMPTY.ordinal(), tr("Empty")},
        {RecordType::CREDIT_CARD.ordinal(), tr("Credit Card")},
        {RecordType::PASSWORD.ordinal(), tr("Password")},
    };
}
