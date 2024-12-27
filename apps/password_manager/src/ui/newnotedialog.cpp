//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "newnotedialog.h"
#include "card.h"
#include "timeutil.h"
#include "ui_newnotedialog.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) : QDialog(parent), ui{std::make_unique<Ui::NewNoteDialog>()} {
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog() {
}

std::shared_ptr<Card> NewNoteDialog::note() const {
    return std::make_shared<Card>(ui->titleEdit->text(), TimeUtil::currentTimeMillis());
}
