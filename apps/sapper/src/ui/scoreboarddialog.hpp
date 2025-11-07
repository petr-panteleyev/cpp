//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "boardsize.hpp"
#include "scoreboarditemmodel.hpp"
#include <QDialog>

namespace Ui {
class ScoreBoardDialog;
}
class ScoreBoard;

class ScoreBoardDialog : public QDialog {
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
