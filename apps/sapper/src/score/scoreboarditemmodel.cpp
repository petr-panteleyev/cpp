//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "scoreboarditemmodel.h"
#include <format>

namespace {

constexpr auto TIME_FORMAT{"{0:%T}"};
constexpr auto DATE_FORMAT{"{0:%d.%m.%Y}"};

} // namespace

ScoreBoardItemModel::ScoreBoardItemModel(QObject *parent, const ScoreBoard &scoreBoard) : QAbstractItemModel(parent) {
}

QVariant ScoreBoardItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
        case 0: return "";
        case 1: return "Время";
        case 2: return "Дата";
        default: return QVariant();
    }
}

QVariant ScoreBoardItemModel::data(const QModelIndex &index, int role) const {
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

void ScoreBoardItemModel::setScores(const std::span<GameScore> &scores) {
    beginResetModel();
    scores_ = std::vector<GameScore>(scores.begin(), scores.end());
    endResetModel();
}
