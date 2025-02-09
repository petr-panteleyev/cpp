//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "newnotedialog.h"
#include "timeutil.h"
#include "ui_newnotedialog.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) : QDialog(parent), ui{std::make_unique<Ui::NewNoteDialog>()} {
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog() {
}

Card NewNoteDialog::note() const {
    return Card(ui->titleEdit->text(), TimeUtil::currentTimeMillis());
}
