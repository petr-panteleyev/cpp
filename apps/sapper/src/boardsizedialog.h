//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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
