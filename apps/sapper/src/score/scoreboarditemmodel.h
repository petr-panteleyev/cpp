//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "gamescore.h"
#include <QAbstractItemModel>
#include <span>

class ScoreBoard;

class ScoreBoardItemModel final : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int COLUMN_INDEX = 0;
    static constexpr int COLUMN_TIME = 1;
    static constexpr int COLUMN_DATE = 2;

  public:
    explicit ScoreBoardItemModel(QObject *parent, const ScoreBoard &scoreBoard);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = TOP_LEVEL) const override {
        return createIndex(row, column);
    }
    virtual QModelIndex parent(const QModelIndex &index) const override { return TOP_LEVEL; };

    virtual int rowCount(const QModelIndex &parent = TOP_LEVEL) const override { return scores_.size(); };
    virtual int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 3; };

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setScores(const std::span<GameScore> &scores);

  private:
    std::vector<GameScore> scores_;

    static constexpr QModelIndex TOP_LEVEL = QModelIndex();
};
