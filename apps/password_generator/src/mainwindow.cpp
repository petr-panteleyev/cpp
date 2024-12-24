/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>

static const std::vector<int> password_length_options = {4, 6, 8, 16, 24, 32, 40, 48, 56, 64};
static const int DEFAULT_LENGTH_INDEX = 3;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
    ui->setupUi(this);

    this->setWindowTitle(tr("Password Generator"));

    // Setup length combobox
    for (auto length : password_length_options) {
        ui->lengthComboBox->addItem(QString::number(length), QVariant(length));
    }
    ui->lengthComboBox->setCurrentIndex(DEFAULT_LENGTH_INDEX);

    visualizeOptions(pwdgen::MEDIUM_OPTIONS);

    // Connect actions
    connect(ui->actionGenerate, &QAction::triggered, this, &MainWindow::onActionGenerate);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExit);
    connect(ui->actionUNIX, &QAction::triggered, this, &MainWindow::onActionUnix);
    connect(ui->actionPIN, &QAction::triggered, this, &MainWindow::onActionPin);
    connect(ui->actionMedium_Password, &QAction::triggered, this, &MainWindow::onActionMediumPassword);
    connect(ui->actionLong_Password, &QAction::triggered, this, &MainWindow::onActionLongPassword);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::onActionCopy);
}

MainWindow::~MainWindow() {
}

void MainWindow::onActionGenerate() {
    auto options = pwdgen::PasswordGeneratorOptions{
        ui->upperCaseCheck->isChecked(), ui->lowerCaseCheck->isChecked(),           ui->digitsCheck->isChecked(),
        ui->symbolsCheck->isChecked(),   ui->lengthComboBox->currentData().toInt(),
    };
    generate(options);
}

void MainWindow::onActionExit() {
    close();
}

void MainWindow::onActionUnix() {
    generate(pwdgen::UNIX_OPTIONS);
}

void MainWindow::onActionPin() {
    generate(pwdgen::PIN_OPTIONS);
}

void MainWindow::onActionMediumPassword() {
    generate(pwdgen::MEDIUM_OPTIONS);
}

void MainWindow::onActionLongPassword() {
    generate(pwdgen::LONG_OPTIONS);
}

void MainWindow::generate(const pwdgen::PasswordGeneratorOptions &options) {
    visualizeOptions(options);

    try {
        auto password = pwdgen::generate(options);
        ui->passwordEdit->setText(password.c_str());
    } catch (pwdgen::PasswordGeneratorException &e) {
        ui->passwordEdit->setText("Error");
    }
}

void MainWindow::visualizeOptions(const pwdgen::PasswordGeneratorOptions &options) {
    ui->upperCaseCheck->setChecked(options.useUpperCase);
    ui->lowerCaseCheck->setChecked(options.useLowerCase);
    ui->digitsCheck->setChecked(options.useDigits);
    ui->symbolsCheck->setChecked(options.useSymbols);

    auto index = ui->lengthComboBox->findData(QVariant(options.length));
    ui->lengthComboBox->setCurrentIndex(index);
}

void MainWindow::onActionCopy() {
    auto text = ui->passwordEdit->text();

    auto clipboard = QGuiApplication::clipboard();
    if (clipboard != nullptr && text.size() != 0) {
        clipboard->setText(text);
    }
}
