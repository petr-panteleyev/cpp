/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include "fieldtype.h"
#include "importrecord.h"
#include "recordtype.h"
#include "settings.h"
#include <QObject>
#include <unordered_map>

class Translations final : public QObject {
    Q_OBJECT

  private:
    Translations() = delete;

  public:
    static const QString translate(const FieldType &type) { return fieldTypeTranslated_.at(type.ordinal()); }
    static const QString translate(const RecordType &type) { return recordTypeTranslated_.at(type.ordinal()); }
    static const QString translate(ImportAction action) { return importActionTranslated_.at(action); }
    static const QString translate(Settings::PasswordType type) { return passwordSettingTranslated_.at(type); }

    static void initialize();

  private:
    static std::unordered_map<unsigned, QString>               fieldTypeTranslated_;
    static std::unordered_map<unsigned, QString>               recordTypeTranslated_;
    static std::unordered_map<ImportAction, QString>           importActionTranslated_;
    static std::unordered_map<Settings::PasswordType, QString> passwordSettingTranslated_;
};

#endif // TRANSLATIONS_H
