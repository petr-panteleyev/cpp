/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef SCOREBOARDDIALOG_H
#define SCOREBOARDDIALOG_H

#include "scoreboard.h"
#include "scoreboarditemmodel.h"
#include <QDialog>

namespace Ui {
class ScoreBoardDialog;
}

class ScoreBoardDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ScoreBoardDialog(QWidget *parent, const ScoreBoard &scoreBoard);
    ~ScoreBoardDialog();

    void setup();

  private:
    void onBoardSizeComboBoxIndexChanged(int index);

  private:
    Ui::ScoreBoardDialog *ui;

    const ScoreBoard &scoreBoard_;
    ScoreBoardItemModel model_;
    std::vector<BoardSize> boardSizes_;
};

#endif // SCOREBOARDDIALOG_H
