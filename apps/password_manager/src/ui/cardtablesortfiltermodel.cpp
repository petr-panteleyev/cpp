//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardtablesortfiltermodel.hpp"
#include "card.hpp"
#include "cardtableitemmodel.hpp"

namespace {

int compareByActive(const Card &left, const Card &right) {
    if (left.active() == right.active()) return 0;
    if (!left.active() && right.active())
        return -1;
    else
        return 1;
}

int compareByFavorite(const Card &left, const Card &right) {
    if (left.favorite() == right.favorite()) return 0;
    if (left.favorite() && !right.favorite())
        return -1;
    else
        return 1;
}

int compareByName(const Card &left, const Card &right) {
    if (left.name() == right.name()) return 0;
    if (left.name() < right.name())
        return -1;
    else
        return 1;
}

} // namespace

bool CardTableSortFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    auto model = (CardTableItemModel *)sourceModel();
    const auto &leftCard = model->cardAtIndex(left.row());
    const auto &rightCard = model->cardAtIndex(right.row());

    auto cmp = ::compareByActive(leftCard, rightCard);
    if (cmp == 0) {
        cmp = ::compareByFavorite(leftCard, rightCard);
    }
    if (cmp == 0) {
        cmp = ::compareByName(leftCard, rightCard);
    }
    return cmp == -1;
}

bool CardTableSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto model = (CardTableItemModel *)sourceModel();
    const auto &card = model->cardAtIndex(sourceRow);

    if (!showDeleted_ && !card.active()) {
        return false;
    }

    if (filterText_.isEmpty()) {
        return true;
    }

    return QString(card.name()).toLower().contains(filterText_.toLower());
}
