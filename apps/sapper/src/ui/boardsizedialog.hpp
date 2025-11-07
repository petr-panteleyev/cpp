//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "boardsize.hpp"
#include "ui_boardsizedialog.h"
#include <QDialog>
#include <QSlider>

class BoardSizeDialog final : public QDialog {

  public:
    explicit BoardSizeDialog(QWidget *parent);
    ~BoardSizeDialog() {}

    BoardSize boardSize() const;

  private:
    void adjustMinesSlider();

  private:
    std::unique_ptr<Ui::BoardSizeDialog> ui;
};
