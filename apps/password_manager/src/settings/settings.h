//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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
using PasswordTypePtrMap = std::unordered_map<PasswordType, std::unique_ptr<pwdgen::PasswordGeneratorOptions>>;
using FontPtrMap = std::unordered_map<FontType, QFont>;

void setColors(const ColorMap &colors);
QColor getColor(Color type);

void setPasswordOptions(const PasswordTypePtrMap &passwords);
std::unique_ptr<pwdgen::PasswordGeneratorOptions> getPasswordOptions(PasswordType type);
PasswordTypePtrMap getAllPasswordOptions();

bool getOpenLinkWithDoubleClick();

void setFonts(const FontPtrMap &fonts);
const QFont getFont(FontType type);

void saveWindowDimensions(const QWidget *widget);
void loadWindowDimensions(QWidget *widget);

} // namespace Settings
