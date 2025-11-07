//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "scoreboarditemmodel.hpp"

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
