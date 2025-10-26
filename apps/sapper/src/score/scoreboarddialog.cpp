//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "scoreboarddialog.h"
#include "scoreboard.h"
#include "scoreboarditemmodel.h"
#include "ui_scoreboarddialog.h"
#include <QComboBox>

ScoreBoardDialog::ScoreBoardDialog(QWidget *parent, const ScoreBoard &scoreBoard)
    : QDialog{parent}, scoreBoard_{scoreBoard}, ui(std::make_unique<Ui::ScoreBoardDialog>()),
      model_{new ScoreBoardItemModel{this, scoreBoard_}} {

    ui->setupUi(this);

    ui->scoreTableView->setModel(model_);
    ui->scoreTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->scoreTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    auto header = ui->scoreTableView->horizontalHeader();
    header->setSectionResizeMode(ScoreBoardItemModel::COLUMN_INDEX, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(ScoreBoardItemModel::COLUMN_TIME, QHeaderView::Stretch);
    header->setSectionResizeMode(ScoreBoardItemModel::COLUMN_DATE, QHeaderView::ResizeToContents);

    connect(ui->boardSizeComboBox, &QComboBox::currentIndexChanged, this,
            &ScoreBoardDialog::onBoardSizeComboBoxIndexChanged);
}

ScoreBoardDialog::~ScoreBoardDialog() {
}

void ScoreBoardDialog::setup() {
    auto boardSizes = scoreBoard_.boardSizes();
    boardSizes_.clear();

    ui->boardSizeComboBox->clear();
    std::for_each(boardSizes.rbegin(), boardSizes.rend(), [this](const auto &size) {
        ui->boardSizeComboBox->addItem(QString::fromStdString(size.toString()));
        boardSizes_.push_back(size);
    });

    if (!boardSizes.empty()) {
        onBoardSizeComboBoxIndexChanged(0);
    }
}

void ScoreBoardDialog::onBoardSizeComboBoxIndexChanged(int index) {
    if (boardSizes_.empty()) {
        return;
    }
    auto boardSize = boardSizes_.at(index);
    auto scores = scoreBoard_.scores(boardSize);
    auto vec = std::vector<GameScore>(scores.begin(), scores.end());
    model_->setScores(vec);
}
