/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef SCOREBOARDITEMMODEL_H
#define SCOREBOARDITEMMODEL_H

#include "scoreboard.h"
#include <QAbstractItemModel>
#include <span>

class ScoreBoardItemModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int COLUMN_INDEX = 0;
    static constexpr int COLUMN_TIME = 1;
    static constexpr int COLUMN_DATE = 2;

  public:
    explicit ScoreBoardItemModel(QObject *parent, const ScoreBoard &scoreBoard);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return parentIndex; };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return scores_.size(); };
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setScores(const std::span<GameScore> &scores);

  private:
    const ScoreBoard &scoreBoard_;
    std::vector<GameScore> scores_;

    static const inline QModelIndex parentIndex = QModelIndex();
};

#endif // SCOREBOARDITEMMODEL_H
