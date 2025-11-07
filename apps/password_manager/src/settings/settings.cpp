//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "settings.hpp"
#include "generator.hpp"
#include "qthelpers.hpp"
#include <QFont>
#include <QSettings>
#include <QWidget>
#include <unordered_map>

namespace Settings {

static const QString COLOR_GROUP{"colors"};
static const QString SETTING_CURRENT_FILE{"currentFile"};
static const QString OPEN_LINKS_WITH_DOUBLE_CLICK{"openLinksWithDoubleClick"};

static const QString FONT_GROUP{"fonts"};

static const QString PASSWORDS_GROUP{"passwords"};
static const QString PASSWORD_LENGTH{"length"};
static const QString PASSWORD_USE_UPPER_CASE{"useUpperCase"};
static const QString PASSWORD_USE_LOWER_CASE{"useLowerCase"};
static const QString PASSWORD_USE_DIGITS{"useDigits"};
static const QString PASSWORD_USE_SYMBOLS{"useSymbols"};

static const std::unordered_map<Color, QString> COLOR_NAMES{
    {Color::FieldName, "fieldName"},       {Color::FieldValue, "fieldValue"},
    {Color::ImportAdd, "importAdd"},       {Color::ImportReplace, "importReplace"},
    {Color::ImportDelete, "importDelete"}, {Color::ImportRestore, "importRestore"},
};

static const std::unordered_map<FontType, QString> FONT_NAMES{
    {FontType::TEXT, "text"},
    {FontType::MENU, "menu"},
};

static const ColorMap DEFAULT_COLORS{
    {Color::FieldName, QColor::fromRgb(0, 0, 255)},        {Color::FieldValue, QColor::fromRgb(0, 0, 0)},
    {Color::ImportAdd, QColor::fromRgb(144, 238, 144)},    {Color::ImportReplace, QColor::fromRgb(255, 255, 224)},
    {Color::ImportDelete, QColor::fromRgb(255, 192, 203)}, {Color::ImportRestore, QColor::fromRgb(255, 165, 0)},
};

static const std::unordered_map<PasswordType, QString> PASSWORD_NAMES{
    {PasswordType::Pin, "pin"},
    {PasswordType::Unix, "unix"},
    {PasswordType::Short, "short"},
    {PasswordType::Long, "long"},
};

static const std::unordered_map<PasswordType, pwdgen::PasswordGeneratorOptions> PASSWORD_DEFAULTS{
    {PasswordType::Pin, pwdgen::PIN_OPTIONS},
    {PasswordType::Unix, pwdgen::UNIX_OPTIONS},
    {PasswordType::Short, pwdgen::MEDIUM_OPTIONS},
    {PasswordType::Long, pwdgen::LONG_OPTIONS},
};

void setCurrentFile(const QString &fileName) {
    QSettings settings;
    settings.setValue(SETTING_CURRENT_FILE, fileName);
    settings.sync();
}

QString getCurrentFile() {
    QSettings settings;
    return settings.value(SETTING_CURRENT_FILE, "").toString();
}

void setColors(const ColorMap &colors) {
    QSettings settings;

    settings.beginGroup(COLOR_GROUP);
    for (const auto &entry : colors) {
        settings.setValue(COLOR_NAMES.at(entry.first), entry.second.name());
    }
    settings.endGroup();
    settings.sync();
}

QColor getColor(Color type) {
    QSettings settings;

    auto value = settings.value(COLOR_GROUP + "/" + COLOR_NAMES.at(type));
    if (!value.isValid()) {
        return DEFAULT_COLORS.at(type);
    } else {
        auto color = QColor(value.toString());
        return color.isValid() ? color : DEFAULT_COLORS.at(type);
    }
}

void setPasswordOptions(const PasswordTypePtrMap &passwords) {
    QSettings settings;

    settings.beginGroup(PASSWORDS_GROUP);

    for (const auto &entry : passwords) {
        settings.beginGroup(PASSWORD_NAMES.at(entry.first));
        settings.setValue(PASSWORD_LENGTH, entry.second->length);
        settings.setValue(PASSWORD_USE_UPPER_CASE, entry.second->useUpperCase);
        settings.setValue(PASSWORD_USE_LOWER_CASE, entry.second->useLowerCase);
        settings.setValue(PASSWORD_USE_DIGITS, entry.second->useDigits);
        settings.setValue(PASSWORD_USE_SYMBOLS, entry.second->useSymbols);
        settings.endGroup();
    }

    settings.endGroup();
    settings.sync();
}

std::unique_ptr<pwdgen::PasswordGeneratorOptions> getPasswordOptions(PasswordType type) {
    QSettings settings;

    auto defaults = PASSWORD_DEFAULTS.at(type);

    auto group = PASSWORDS_GROUP + "/" + PASSWORD_NAMES.at(type) + "/";

    bool isOk = false;

    auto length = settings.value(group + PASSWORD_LENGTH, defaults.length).toInt(&isOk);
    if (!isOk) {
        return defaults.copy();
    }

    auto useUpperCase = settings.value(group + PASSWORD_USE_UPPER_CASE, defaults.useUpperCase).toBool();
    auto useLowerCase = settings.value(group + PASSWORD_USE_LOWER_CASE, defaults.useLowerCase).toBool();
    auto useDigits = settings.value(group + PASSWORD_USE_DIGITS, defaults.useDigits).toBool();
    auto useSymbols = settings.value(group + PASSWORD_USE_SYMBOLS, defaults.useSymbols).toBool();
    return std::make_unique<pwdgen::PasswordGeneratorOptions>(useUpperCase, useLowerCase, useDigits, useSymbols,
                                                              length);
}

PasswordTypePtrMap getAllPasswordOptions() {
    PasswordTypePtrMap result;

    for (const auto &entry : PASSWORD_DEFAULTS) {
        auto options = getPasswordOptions(entry.first);
        result[entry.first] = std::move(options);
    }

    return result;
}

bool getOpenLinkWithDoubleClick() {
    QSettings settings;
    return settings.value(OPEN_LINKS_WITH_DOUBLE_CLICK, true).toBool();
}

void setFonts(const FontPtrMap &fonts) {
    QSettings settings;
    settings.beginGroup(FONT_GROUP);
    for (const auto &f : fonts) {
        settings.setValue(FONT_NAMES.at(f.first), f.second.toString());
    }
    settings.endGroup();
}

const QFont getFont(FontType type) {
    QSettings settings;
    settings.beginGroup(FONT_GROUP);

    auto str = settings.value(FONT_NAMES.at(type), "System").toString();
    QFont font;
    font.fromString(str);
    settings.endGroup();
    return font;
}

void saveWindowDimensions(const QWidget *widget) {
    QSettings settings;
    QtHelpers::saveWindowDimensions(*widget, settings, "window");
}

void loadWindowDimensions(QWidget *widget) {
    QSettings settings;
    QtHelpers::loadWindowDimensions(*widget, settings, "window");
}

} // namespace Settings
