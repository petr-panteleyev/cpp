//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QClipboard>

MainWindow::~MainWindow() {
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
    ui->setupUi(this);

    // Setup length combobox
    for (auto length : PASSWORD_LENGTH_OPTIONS) {
        ui->lengthComboBox->addItem(QString::number(length), QVariant(length));
    }
    ui->lengthComboBox->setCurrentIndex(DEFAULT_LENGTH_INDEX);

    visualizeOptions(pwdgen::MEDIUM_OPTIONS);

    // Connect actions
    connect(ui->actionGenerate, &QAction::triggered, [this]() {
        generate(pwdgen::PasswordGeneratorOptions{
            ui->upperCaseCheck->isChecked(),
            ui->lowerCaseCheck->isChecked(),
            ui->digitsCheck->isChecked(),
            ui->symbolsCheck->isChecked(),
            ui->lengthComboBox->currentData().toInt(),
        });
    });
    connect(ui->actionExit, &QAction::triggered, [this]() { close(); });
    connect(ui->actionUNIX, &QAction::triggered, [this]() { generate(pwdgen::UNIX_OPTIONS); });
    connect(ui->actionPIN, &QAction::triggered, [this]() { generate(pwdgen::PIN_OPTIONS); });
    connect(ui->actionMedium_Password, &QAction::triggered, [this]() { generate(pwdgen::MEDIUM_OPTIONS); });
    connect(ui->actionLong_Password, &QAction::triggered, [this]() { generate(pwdgen::LONG_OPTIONS); });
    connect(ui->actionCopy, &QAction::triggered, [this]() {
        auto text = ui->passwordEdit->text();
        auto clipboard = QGuiApplication::clipboard();
        if (clipboard != nullptr && !text.isEmpty()) {
            clipboard->setText(text);
        }
    });
}

void MainWindow::visualizeOptions(const pwdgen::PasswordGeneratorOptions &options) {
    ui->upperCaseCheck->setChecked(options.useUpperCase);
    ui->lowerCaseCheck->setChecked(options.useLowerCase);
    ui->digitsCheck->setChecked(options.useDigits);
    ui->symbolsCheck->setChecked(options.useSymbols);

    auto index = ui->lengthComboBox->findData(QVariant(options.length));
    ui->lengthComboBox->setCurrentIndex(index);
}

void MainWindow::generate(const pwdgen::PasswordGeneratorOptions &options) {
    visualizeOptions(options);

    try {
        ui->passwordEdit->setText(QString::fromStdString(pwdgen::generate(options)));
    } catch (pwdgen::PasswordGeneratorException &e) {
        ui->passwordEdit->setText("Ошибка");
    }
}
