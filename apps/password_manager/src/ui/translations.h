//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "importaction.h"
#include "passwordtype.h"
#include <QString>

class FieldType;
class RecordType;

namespace Translations {

void initialize();

QString translate(const FieldType &type);
QString translate(ImportAction action);
QString translate(Settings::PasswordType type);

} // namespace Translations
