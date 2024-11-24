/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <vector>

static const std::vector<int> password_length_options = {4, 6, 8, 16, 24, 32, 40, 48, 56, 64};
static const int              DEFAULT_LENGTH_INDEX    = 3;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setWindowTitle(tr("Password Generator"));

    // Setup length combobox
    for (auto length : password_length_options) {
        ui->lengthComboBox->addItem(QString::number(length), QVariant(length));
    }
    ui->lengthComboBox->setCurrentIndex(DEFAULT_LENGTH_INDEX);

    visualize_options(password_generator::MEDIUM_OPTIONS);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionGenerate_triggered() {
    auto options = password_generator::PasswordGeneratorOptions{
        ui->upperCaseCheck->isChecked(), ui->lowerCaseCheck->isChecked(),           ui->digitsCheck->isChecked(),
        ui->symbolsCheck->isChecked(),   ui->lengthComboBox->currentData().toInt(),
    };
    generate(options);
}

void MainWindow::on_actionExit_triggered() {
    close();
}

void MainWindow::on_actionUNIX_triggered() {
    generate(password_generator::UNIX_OPTIONS);
}

void MainWindow::on_actionPIN_triggered() {
    generate(password_generator::PIN_OPTIONS);
}

void MainWindow::on_actionMedium_Password_triggered() {
    generate(password_generator::MEDIUM_OPTIONS);
}

void MainWindow::on_actionLong_Password_triggered() {
    generate(password_generator::LONG_OPTIONS);
}

void MainWindow::generate(const password_generator::PasswordGeneratorOptions &options) {
    visualize_options(options);

    try {
        auto password = password_generator::generate(options);
        ui->passwordEdit->setText(password.c_str());
    } catch (password_generator::PasswordGeneratorException &e) {
        ui->passwordEdit->setText("Error");
    }
}

void MainWindow::visualize_options(const password_generator::PasswordGeneratorOptions &options) {
    ui->upperCaseCheck->setChecked(options.use_upper_case);
    ui->lowerCaseCheck->setChecked(options.use_lower_case);
    ui->digitsCheck->setChecked(options.use_digits);
    ui->symbolsCheck->setChecked(options.use_symbols);

    auto index = ui->lengthComboBox->findData(QVariant(options.length));
    ui->lengthComboBox->setCurrentIndex(index);
}

void MainWindow::on_actionCopy_triggered() {
    auto text = ui->passwordEdit->text();

    QClipboard *clipboard = QGuiApplication::clipboard();
    if (clipboard != nullptr && text.size() != 0) {
        clipboard->setText(text);
    }
}
