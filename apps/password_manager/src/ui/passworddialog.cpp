//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) : QDialog{parent}, ui{std::make_unique<Ui::PasswordDialog>()} {
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog() {
}

void PasswordDialog::setFileName(const QString &fileName) {
    ui->fileLabel->setText(fileName);
    ui->passwordEdit->setText("");
    ui->passwordEdit->setFocus();
}

const QString PasswordDialog::getFileName() const {
    return ui->fileLabel->text();
}

QString PasswordDialog::getPassword() const {
    return ui->passwordEdit->text();
}
