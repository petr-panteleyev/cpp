//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "translations.h"
#include "fieldtype.h"
#include "recordtype.h"
#include "str.h"

namespace Translations {

std::unordered_map<unsigned, QString> fieldTypeTranslated_;
std::unordered_map<unsigned, QString> recordTypeTranslated_;
std::unordered_map<ImportAction, QString> importActionTranslated_;
std::unordered_map<Settings::PasswordType, QString> passwordSettingTranslated_;

void initialize() {
    fieldTypeTranslated_ = {
        {FieldType::STRING.ordinal(), "Строка"},
        {FieldType::HIDDEN.ordinal(), "Скрытая строка"},
        {FieldType::EMAIL.ordinal(), "E-mail"},
        {FieldType::CREDIT_CARD_NUMBER.ordinal(), "Номер кредитной карты"},
        {FieldType::LINK.ordinal(), "Веб-адрес"},
        {FieldType::PIN.ordinal(), "PIN"},
        {FieldType::UNIX_PASSWORD.ordinal(), "Пароль UNIX"},
        {FieldType::SHORT_PASSWORD.ordinal(), Str::SHORT_PASSWORD},
        {FieldType::LONG_PASSWORD.ordinal(), Str::LONG_PASSWORD},
        {FieldType::CARD_TYPE.ordinal(), "Тип карты"},
        {FieldType::DATE.ordinal(), "Дата"},
        {FieldType::EXPIRATION_MONTH.ordinal(), "Месяц окончания"},
    };

    recordTypeTranslated_ = {
        {RecordType::EMPTY.ordinal(), "Пустая"},
        {RecordType::CREDIT_CARD.ordinal(), "Кредитная карта"},
        {RecordType::PASSWORD.ordinal(), Str::PASSWORD},
    };

    importActionTranslated_ = {
        {ImportAction::ADD, Str::ADD},         {ImportAction::DELETE, Str::DELETE},
        {ImportAction::REPLACE, Str::REPLACE}, {ImportAction::RESTORE, Str::RESTORE},
        {ImportAction::SKIP, Str::SKIP},
    };

    passwordSettingTranslated_ = {
        {Settings::PasswordType::Pin, "PIN"},
        {Settings::PasswordType::Unix, "Пароль UNIX"},
        {Settings::PasswordType::Short, Str::SHORT_PASSWORD},
        {Settings::PasswordType::Long, Str::LONG_PASSWORD},
    };
}

QString translate(const FieldType &type) {
    return fieldTypeTranslated_.at(type.ordinal());
}

QString translate(const RecordType &type) {
    return recordTypeTranslated_.at(type.ordinal());
}

QString translate(ImportAction action) {
    return importActionTranslated_.at(action);
}

QString translate(Settings::PasswordType type) {
    return passwordSettingTranslated_.at(type);
}

} // namespace Translations
