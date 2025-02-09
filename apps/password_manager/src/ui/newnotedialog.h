//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include "card.h"
#include <QDialog>
#include <memory>

namespace Ui {
class NewNoteDialog;
}

class NewNoteDialog : public QDialog {
    Q_OBJECT

  public:
    explicit NewNoteDialog(QWidget *parent);
    ~NewNoteDialog();

    Card note() const;

  private:
    std::unique_ptr<Ui::NewNoteDialog> ui;
};

#endif // NEWNOTEDIALOG_H
