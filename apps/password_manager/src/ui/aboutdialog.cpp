/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDate>

#define str(s) #s
#define xstr(s) str(s)

#ifdef PROJECT_VERSION
static const QString projectVersion{xstr(PROJECT_VERSION)};
#else
static const QString projectVersion{"NOT DEFINED"};
#endif

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->versionLabel->setText(projectVersion);
    // TODO: real date
    ui->buildDateLabel->setText(QDate::currentDate().toString());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
