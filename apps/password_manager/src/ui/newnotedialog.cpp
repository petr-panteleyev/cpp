//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "newnotedialog.hpp"
#include "timeutil.hpp"
#include "ui_newnotedialog.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) : QDialog(parent), ui{std::make_unique<Ui::NewNoteDialog>()} {
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog() {
}

Card NewNoteDialog::note() const {
    return Card(ui->titleEdit->text(), TimeUtil::currentTimeMillis());
}
