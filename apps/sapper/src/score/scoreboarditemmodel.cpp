//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "scoreboarditemmodel.h"

ScoreBoardItemModel::ScoreBoardItemModel(QObject *parent, const ScoreBoard &scoreBoard) : QAbstractItemModel(parent) {
}

QVariant ScoreBoardItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
        case 0: return "";
        case 1: return tr("Time");
        case 2: return tr("Date");
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
        case COLUMN_TIME: return score.time.toString("HH:mm:ss.zzz");
        case COLUMN_DATE: return score.date.toString("dd.MM.yyyy");
    }

    return QVariant();
}

void ScoreBoardItemModel::setScores(const std::span<GameScore> &scores) {
    beginResetModel();
    scores_ = std::vector<GameScore>(scores.begin(), scores.end());
    endResetModel();
}
