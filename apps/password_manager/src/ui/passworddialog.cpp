/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PasswordDialog) {
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog() {
    delete ui;
}

void PasswordDialog::setFileName(const QString &fileName) {
    ui->fileLabel->setText(fileName);
    ui->passwordEdit->setText("");
}

const QString PasswordDialog::getFileName() const {
    return ui->fileLabel->text();
}

QString PasswordDialog::getPassword() const {
    return ui->passwordEdit->text();
}
