//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "translations.h"
#include "fieldtype.h"
#include "recordtype.h"
#include <QApplication>

namespace Translations {

std::unordered_map<unsigned, QString> fieldTypeTranslated_;
std::unordered_map<unsigned, QString> recordTypeTranslated_;
std::unordered_map<ImportAction, QString> importActionTranslated_;
std::unordered_map<Settings::PasswordType, QString> passwordSettingTranslated_;

void initialize() {
    fieldTypeTranslated_ = {
        {FieldType::STRING.ordinal(), QApplication::translate("FieldType", "String")},
        {FieldType::HIDDEN.ordinal(), QApplication::translate("FieldType", "Hidden String")},
        {FieldType::EMAIL.ordinal(), QApplication::translate("FieldType", "E-mail")},
        {FieldType::CREDIT_CARD_NUMBER.ordinal(), QApplication::translate("FieldType", "Credit Card Number")},
        {FieldType::LINK.ordinal(), QApplication::translate("FieldType", "Web Link")},
        {FieldType::PIN.ordinal(), QApplication::translate("FieldType", "PIN code")},
        {FieldType::UNIX_PASSWORD.ordinal(), QApplication::translate("FieldType", "UNIX password")},
        {FieldType::SHORT_PASSWORD.ordinal(), QApplication::translate("FieldType", "Short password")},
        {FieldType::LONG_PASSWORD.ordinal(), QApplication::translate("FieldType", "Long password")},
        {FieldType::CARD_TYPE.ordinal(), QApplication::translate("FieldType", "Card type")},
        {FieldType::DATE.ordinal(), QApplication::translate("FieldType", "Date")},
        {FieldType::EXPIRATION_MONTH.ordinal(), QApplication::translate("FieldType", "Expiration Month")},
    };

    recordTypeTranslated_ = {
        {RecordType::EMPTY.ordinal(), QApplication::translate("NewRecordType", "Empty")},
        {RecordType::CREDIT_CARD.ordinal(), QApplication::translate("NewRecordType", "Credit Card")},
        {RecordType::PASSWORD.ordinal(), QApplication::translate("NewRecordType", "Password")},
    };

    importActionTranslated_ = {
        {ImportAction::ADD, QApplication::translate("ImportAction", "Add")},
        {ImportAction::DELETE, QApplication::translate("ImportAction", "Delete")},
        {ImportAction::REPLACE, QApplication::translate("ImportAction", "Replace")},
        {ImportAction::RESTORE, QApplication::translate("ImportAction", "Restore")},
        {ImportAction::SKIP, QApplication::translate("ImportAction", "Skip")},
    };

    passwordSettingTranslated_ = {
        {Settings::PasswordType::Pin, "PIN"},
        {Settings::PasswordType::Unix, QApplication::translate("PasswordType", "UNIX password")},
        {Settings::PasswordType::Short, QApplication::translate("PasswordType", "Short password")},
        {Settings::PasswordType::Long, QApplication::translate("PasswordType", "Long password")},
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
