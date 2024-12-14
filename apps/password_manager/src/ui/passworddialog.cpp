/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent, const QString &fileName) : QDialog(parent), ui(new Ui::PasswordDialog) {
    ui->setupUi(this);
    ui->fileLabel->setText(fileName);
}

PasswordDialog::~PasswordDialog() {
    delete ui;
}

QString PasswordDialog::password() const {
    return ui->passwordEdit->text();
}
