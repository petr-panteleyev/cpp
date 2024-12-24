//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include <QPushButton>

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent)
    : QDialog{parent}, ui{std::make_unique<Ui::ChangePasswordDialog>()} {
    ui->setupUi(this);

    enabledColors_.setColor(QPalette::Text, Qt::black);
    enabledColors_.setColor(QPalette::Base, QColor::fromRgb(0xFF, 0xFF, 0xFF));

    disabledColors_.setColor(QPalette::Text, Qt::black);
    disabledColors_.setColor(QPalette::Base, QColor::fromRgb(0xFF, 0xC0, 0xCB));
}

ChangePasswordDialog::~ChangePasswordDialog() {
}

void ChangePasswordDialog::reset(const QString &fileName) {
    ui->fileLabel->setText(fileName);
    ui->passwordEdit->setText("");
    ui->repeatEdit->setText("");
    ui->passwordEdit->setFocus();
}

QString ChangePasswordDialog::password() const {
    return ui->passwordEdit->text();
}

void ChangePasswordDialog::done(int code) {
    if (code != QDialog::Accepted) {
        return QDialog::done(code);
    }

    if (ui->passwordEdit->text() != ui->repeatEdit->text()) {
        return;
    }
    return QDialog::done(code);
}

void ChangePasswordDialog::on_passwordEdit_textChanged(const QString &text) {
    setEditBackground(text != ui->repeatEdit->text());
}

void ChangePasswordDialog::on_repeatEdit_textChanged(const QString &text) {
    setEditBackground(text != ui->passwordEdit->text());
}

void ChangePasswordDialog::setEditBackground(bool disabled) {
    const QPalette &palette = disabled ? disabledColors_ : enabledColors_;
    ui->repeatEdit->setPalette(palette);
    ui->passwordEdit->setPalette(palette);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!disabled);
}
