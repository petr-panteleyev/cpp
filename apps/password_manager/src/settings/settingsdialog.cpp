//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "settingsdialog.h"
#include "fonttype.h"
#include "qcheckbox.h"
#include "qcombobox.h"
#include "qthelpers.h"
#include "settings.h"
#include "translations.h"
#include "ui_settingsdialog.h"
#include <QColorDialog>
#include <QFontDialog>

static const std::array<int, 6> LENGTH{4, 6, 8, 16, 24, 32};

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(std::make_unique<Ui::SettingsDialog>()) {
    ui->setupUi(this);

    setupColorButtons(true);
    setupFontButtons();

    for (const auto &entry : Settings::getAllPasswordOptions()) {
        passwords_[entry.first] = entry.second;
        ui->passwordTypeComboBox->addItem(Translations::translate(entry.first), QVariant::fromValue(entry.first));
    }
    connect(ui->passwordTypeComboBox, &QComboBox::currentIndexChanged, this, &SettingsDialog::onPasswordTypeSelected);

    for (auto length : LENGTH) {
        ui->passwordLengthComboBox->addItem(QString::number(length), length);
    }
    connect(ui->passwordLengthComboBox, &QComboBox::currentIndexChanged, this,
            &SettingsDialog::onPasswordLengthSelected);

    connect(ui->upperCaseCheckBox, &QCheckBox::clicked, [this](bool checked) {
        auto type = ui->passwordTypeComboBox->currentData().value<Settings::PasswordType>();
        passwords_.at(type)->useUpperCase = checked;
    });
    connect(ui->lowerCaseCheckBox, &QCheckBox::clicked, [this](bool checked) {
        auto type = ui->passwordTypeComboBox->currentData().value<Settings::PasswordType>();
        passwords_.at(type)->useLowerCase = checked;
    });
    connect(ui->digitsCheckBox, &QCheckBox::clicked, [this](bool checked) {
        auto type = ui->passwordTypeComboBox->currentData().value<Settings::PasswordType>();
        passwords_.at(type)->useDigits = checked;
    });
    connect(ui->symbolsCheckBox, &QCheckBox::clicked, [this](bool checked) {
        auto type = ui->passwordTypeComboBox->currentData().value<Settings::PasswordType>();
        passwords_.at(type)->useSymbols = checked;
    });
}

SettingsDialog::~SettingsDialog() {
}

void SettingsDialog::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    ui->tabWidget->setCurrentIndex(0);
    if (ui->passwordTypeComboBox->currentIndex() != 0) {
        ui->passwordTypeComboBox->setCurrentIndex(0);
    } else {
        onPasswordTypeSelected(0);
    }
}

void SettingsDialog::setupColorButtons(bool connectSignal) {
    setupColorButton(Settings::Color::FieldName, ui->fieldNameColorButton, connectSignal);
    setupColorButton(Settings::Color::FieldValue, ui->fieldValueColorButton, connectSignal);
    setupColorButton(Settings::Color::ImportAdd, ui->importAddColorButton, connectSignal);
    setupColorButton(Settings::Color::ImportReplace, ui->importReplaceColorButton, connectSignal);
    setupColorButton(Settings::Color::ImportDelete, ui->importDeleteColorButton, connectSignal);
    setupColorButton(Settings::Color::ImportRestore, ui->importRestoreColorButton, connectSignal);
}

void SettingsDialog::setupColorButton(Settings::Color color, QPushButton *button, bool connectSignal) {
    auto qColor = Settings::getColor(color);
    colors_[color] = qColor;
    button->setStyleSheet("background-color: " + qColor.name());
    if (connectSignal) {
        connect(button, &QPushButton::clicked, [this, color, button]() { onFieldNameColorButton(color, button); });
    }
}

void SettingsDialog::setupFontButtons() {
    auto textFont = Settings::getFont(Settings::FontType::TEXT);
    ui->textFontEdit->setText(QString("%1, %2").arg(textFont.family()).arg(textFont.pointSize()));
    connect(ui->textFontButton, &QPushButton::clicked,
            [this]() { onFontButtonClicked(Settings::FontType::TEXT, ui->textFontEdit); });

    auto menuFont = Settings::getFont(Settings::FontType::MENU);
    ui->menuFontEdit->setText(QString("%1, %2").arg(menuFont.family()).arg(menuFont.pointSize()));
    connect(ui->menuFontButton, &QPushButton::clicked,
            [this]() { onFontButtonClicked(Settings::FontType::MENU, ui->menuFontEdit); });
}

void SettingsDialog::done(int code) {
    if (code == QDialog::Accepted) {
        Settings::setColors(colors_);
        Settings::setPasswordOptions(passwords_);
        Settings::setFonts(fonts_);
    } else {
        // Reset controls to current settings
        setupColorButtons(false);
        for (const auto &entry : Settings::getAllPasswordOptions()) {
            passwords_[entry.first] = entry.second;
        }
    }
    QDialog::done(code);
}

void SettingsDialog::onFieldNameColorButton(Settings::Color color, QPushButton *button) {
    auto currentColor = Settings::getColor(color);
    auto newColor = QColorDialog::getColor(currentColor, parentWidget());
    if (newColor.isValid() && newColor != currentColor) {
        button->setStyleSheet("background-color: " + newColor.name());
        colors_[color] = newColor;
    }
}

void SettingsDialog::onPasswordTypeSelected(int index) {
    auto type = ui->passwordTypeComboBox->itemData(index).value<Settings::PasswordType>();
    auto options = passwords_.at(type);
    ui->upperCaseCheckBox->setChecked(options->useUpperCase);
    ui->lowerCaseCheckBox->setChecked(options->useLowerCase);
    ui->digitsCheckBox->setChecked(options->useDigits);
    ui->symbolsCheckBox->setChecked(options->useSymbols);

    auto lengthIndex = QtHelpers::indexOfData(*ui->passwordLengthComboBox, options->length, Qt::UserRole);
    if (lengthIndex != -1) {
        ui->passwordLengthComboBox->setCurrentIndex(lengthIndex);
    }
}

void SettingsDialog::onPasswordLengthSelected(int index) {
    auto type = ui->passwordTypeComboBox->currentData().value<Settings::PasswordType>();
    auto length = ui->passwordLengthComboBox->itemData(index).toInt();
    passwords_.at(type)->length = length;
}

void SettingsDialog::onFontButtonClicked(Settings::FontType fontType, QLineEdit *fontEdit) {
    auto font = Settings::getFont(fontType);
    bool ok;
    font = QFontDialog::getFont(&ok, font, parentWidget());
    if (ok) {
        fontEdit->setText(font.family() + " " + QString::number(font.pointSize()));
        fonts_[fontType] = std::make_shared<QFont>(font);
    }
}
