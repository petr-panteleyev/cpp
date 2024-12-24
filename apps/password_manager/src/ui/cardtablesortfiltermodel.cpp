//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardtablesortfiltermodel.h"
#include "card.h"
#include "cardtableitemmodel.h"

static int compareByActive(const Card &left, const Card &right) {
    if (left.active() == right.active())
        return 0;
    if (!left.active() && right.active())
        return -1;
    else
        return 1;
}

static int compareByFavorite(const Card &left, const Card &right) {
    if (left.favorite() == right.favorite())
        return 0;
    if (left.favorite() && !right.favorite())
        return -1;
    else
        return 1;
}

static int compareByName(const Card &left, const Card &right) {
    if (left.name() == right.name())
        return 0;
    if (left.name() < right.name())
        return -1;
    else
        return 1;
}

bool CardTableSortFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    auto model = (CardTableItemModel *)sourceModel();
    auto leftCard = model->cardAtIndex(left.row());
    auto rightCard = model->cardAtIndex(right.row());

    auto cmp = compareByActive(*leftCard, *rightCard);
    if (cmp == 0) {
        cmp = compareByFavorite(*leftCard, *rightCard);
    }
    if (cmp == 0) {
        cmp = compareByName(*leftCard, *rightCard);
    }
    return cmp == -1;
}

bool CardTableSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto model = (CardTableItemModel *)sourceModel();
    auto card = model->cardAtIndex(sourceRow);

    if (!show_deleted_ && !card->active()) {
        return false;
    }

    if (filterText_.isEmpty()) {
        return true;
    }

    return card->name().toLower().contains(filterText_.toLower());
}
