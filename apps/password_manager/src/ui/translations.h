//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include "importaction.h"
#include "passwordtype.h"
#include <QString>

class FieldType;
class RecordType;

namespace Translations {

void initialize();

QString translate(const FieldType &type);
QString translate(const RecordType &type);
QString translate(ImportAction action);
QString translate(Settings::PasswordType type);

} // namespace Translations

#endif // TRANSLATIONS_H
