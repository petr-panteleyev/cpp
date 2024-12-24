//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SETTINGS_H
#define SETTINGS_H

#include "generator.h"
#include "passwordtype.h"
#include <QColor>
#include <QString>

namespace Settings {

void setCurrentFile(const QString &fileName);
QString getCurrentFile();

enum class Color {
    FieldName,
    FieldValue,
    ImportAdd,
    ImportReplace,
    ImportDelete,
    ImportRestore,
};

using ColorMap = std::unordered_map<Color, QColor>;

using PasswordTypePtrMap = std::unordered_map<PasswordType, std::shared_ptr<pwdgen::PasswordGeneratorOptions>>;

void setColors(const ColorMap &colors);
QColor getColor(Color type);

void setPasswordOptions(const PasswordTypePtrMap &passwords);
pwdgen::PasswordGeneratorOptions getPasswordOptions(PasswordType type);
PasswordTypePtrMap getAllPasswordOptions();

bool getOpenLinkWithDoubleClick();

} // namespace Settings

#endif // SETTINGS_H
