/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "newnotedialog.h"
#include "ui_newnotedialog.h"
#include "timeutil.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNoteDialog)
{
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog()
{
    delete ui;
}

CardPtr NewNoteDialog::note() const {
    return std::make_shared<Card>(ui->titleEdit->text(), TimeUtil::currentTimeMillis());
}
