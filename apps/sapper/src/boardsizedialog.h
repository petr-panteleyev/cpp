//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef BOARDSIZEDIALOG_H
#define BOARDSIZEDIALOG_H

#include "boardsize.h"
#include <QDialog>
#include <memory>

namespace Ui {
class BoardSizeDialog;
}

class BoardSizeDialog final : public QDialog {
    Q_OBJECT

  public:
    explicit BoardSizeDialog(QWidget *parent);
    ~BoardSizeDialog();

    BoardSize boardSize() const;

  private:
    std::unique_ptr<Ui::BoardSizeDialog> ui;
};

#endif // BOARDSIZEDIALOG_H
