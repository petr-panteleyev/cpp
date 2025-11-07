//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "gamescore.hpp"
#include "scoreboard.hpp"
#include <QAbstractItemModel>

class ScoreBoardItemModel final : public QAbstractItemModel {
  public:
    static constexpr int COLUMN_INDEX = 0;
    static constexpr int COLUMN_TIME = 1;
    static constexpr int COLUMN_DATE = 2;

  public:
    explicit ScoreBoardItemModel(QObject *parent, const ScoreBoard &scoreBoard) : QAbstractItemModel(parent) {}

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = TOP_LEVEL) const override {
        return createIndex(row, column);
    }
    virtual QModelIndex parent(const QModelIndex &index) const override { return TOP_LEVEL; };

    virtual int rowCount(const QModelIndex &parent = TOP_LEVEL) const override { return scores_.size(); };
    virtual int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 3; };

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        auto score = scores_.at(index.row());

        switch (index.column()) {
            case COLUMN_INDEX: return QString::number(index.row() + 1);
            case COLUMN_TIME: return QString::fromStdString(std::format(TIME_FORMAT, score.seconds_));
            case COLUMN_DATE: return QString::fromStdString(std::format(DATE_FORMAT, score.date_));
        }

        return QVariant();
    }

    void setScores(const std::span<GameScore> &scores) {
        beginResetModel();
        scores_ = std::vector<GameScore>(scores.begin(), scores.end());
        endResetModel();
    }

  private:
    static constexpr auto TIME_FORMAT{"{0:%T}"};
    static constexpr auto DATE_FORMAT{"{0:%d.%m.%Y}"};

  private:
    std::vector<GameScore> scores_;

    static constexpr QModelIndex TOP_LEVEL = QModelIndex();
};
