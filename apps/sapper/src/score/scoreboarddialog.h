//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SCOREBOARDDIALOG_H
#define SCOREBOARDDIALOG_H

#include "boardsize.h"
#include <QDialog>

namespace Ui {
class ScoreBoardDialog;
}

class ScoreBoard;
class ScoreBoardItemModel;

class ScoreBoardDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ScoreBoardDialog(QWidget *parent, const ScoreBoard &scoreBoard);
    ~ScoreBoardDialog();

    void setup();

  private:
    void onBoardSizeComboBoxIndexChanged(int index);

  private:
    const ScoreBoard &scoreBoard_;
    std::vector<BoardSize> boardSizes_;

    std::unique_ptr<Ui::ScoreBoardDialog> ui;
    ScoreBoardItemModel *model_;
};

#endif // SCOREBOARDDIALOG_H
