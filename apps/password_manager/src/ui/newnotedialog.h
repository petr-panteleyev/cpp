/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include "card.h"
#include <QDialog>

namespace Ui {
class NewNoteDialog;
}

class NewNoteDialog : public QDialog {
    Q_OBJECT

  public:
    explicit NewNoteDialog(QWidget *parent = nullptr);
    ~NewNoteDialog();

    CardPtr note() const;

  private:
    Ui::NewNoteDialog *ui;
};

#endif // NEWNOTEDIALOG_H
