//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef BOARDSIZEDIALOG_H
#define BOARDSIZEDIALOG_H

#include "boardsize.h"
#include <QDialog>

namespace Ui {
class BoardSizeDialog;
}

class BoardSizeDialog final : public QDialog {
    Q_OBJECT

  public:
    explicit BoardSizeDialog(QWidget *parent = nullptr);
    ~BoardSizeDialog();

    BoardSize boardSize() const;

  private:
    void adjustMinesSlider();
    void onWidthValueChanged(int);
    void onHeightValueChanged(int);
    void onMinesValueChanged(int);

  private:
    Ui::BoardSizeDialog *ui;
};

#endif // BOARDSIZEDIALOG_H
