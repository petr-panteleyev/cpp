/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include "fieldtype.h"
#include <QObject>
#include <unordered_map>

class Translations final : public QObject {
    Q_OBJECT

  private:
    Translations() = delete;

  public:
    static const QString translate(const FieldType &type) { return fieldTypeTranslated_.at(type.ordinal()); }
    static void          initialize();

  private:
    static std::unordered_map<unsigned, QString> fieldTypeTranslated_;
};

#endif // TRANSLATIONS_H
