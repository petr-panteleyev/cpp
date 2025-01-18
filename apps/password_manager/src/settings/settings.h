//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SETTINGS_H
#define SETTINGS_H

#include "fonttype.h"
#include "generator.h"
#include "passwordtype.h"
#include <QColor>
#include <QString>
#include <unordered_map>

class QFont;
class QWidget;

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
using FontPtrMap = std::unordered_map<FontType, std::shared_ptr<QFont>>;

void setColors(const ColorMap &colors);
QColor getColor(Color type);

void setPasswordOptions(const PasswordTypePtrMap &passwords);
pwdgen::PasswordGeneratorOptions getPasswordOptions(PasswordType type);
PasswordTypePtrMap getAllPasswordOptions();

bool getOpenLinkWithDoubleClick();

void setFonts(const FontPtrMap &fonts);
const QFont getFont(FontType type);

void saveWindowDimensions(const QWidget *widget);
void loadWindowDimensions(QWidget *widget);

} // namespace Settings

#endif // SETTINGS_H
