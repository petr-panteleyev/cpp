/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "version.h"
#include <QDate>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);

    ui->versionLabel->setText(QString::fromStdString(Version::projectVersion));
    ui->buildDateLabel->setText(QDate::currentDate().toString());
}

AboutDialog::~AboutDialog() {
    delete ui;
}
