/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include "fieldtype.h"
#include "recordtype.h"
#include <QObject>
#include <unordered_map>

class Translations final : public QObject {
    Q_OBJECT

  private:
    Translations() = delete;

  public:
    static const QString translate(const FieldType &type) { return fieldTypeTranslated_.at(type.ordinal()); }
    static const QString translate(const RecordType &type) { return recordTypeTranslated_.at(type.ordinal()); }

    static void initialize();

  private:
    static std::unordered_map<unsigned, QString> fieldTypeTranslated_;
    static std::unordered_map<unsigned, QString> recordTypeTranslated_;
};

#endif // TRANSLATIONS_H
