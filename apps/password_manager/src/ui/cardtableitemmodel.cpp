//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardtableitemmodel.h"
#include "card.h"

namespace {

QVariant buildAuxIconValue(const Card &card) {
    if (!card.active()) {
        return Picture::TRASH.icon();
    } else {
        if (card.favorite()) {
            return Picture::FAVORITES.icon();
        } else {
            return QVariant();
        }
    }
}

} // namespace

QVariant CardTableItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || (std::size_t)index.row() >= data_.size()) {
        return QVariant();
    }

    const auto &card = data_.at(index.row());

    switch (index.column()) {
        case 0: return role == Qt::DecorationRole ? card.picture().icon() : QVariant();
        case 1: return role == Qt::DisplayRole ? card.name() : QVariant();
        case 2: return role == Qt::DecorationRole ? buildAuxIconValue(card) : QVariant();
        default: return QVariant();
    }
}

void CardTableItemModel::replace(int row, const Card &card) {
    data_[row] = card;
    emit dataChanged(createIndex(row, 0), createIndex(row, 2));
}

void CardTableItemModel::addOrReplace(const Card &card) {
    auto found = std::find_if(data_.begin(), data_.end(), [&card](const auto &c) { return c.uuid() == card.uuid(); });
    if (found != data_.end()) {
        auto row = std::distance(data_.begin(), found);
        replace(row, card);
    } else {
        add(card);
    }
}

void CardTableItemModel::add(const Card &card) {
    beginInsertRows(parent_index, data_.size(), data_.size());
    data_.push_back(card);
    endInsertRows();
}

void CardTableItemModel::deleteCard(int row) {
    beginRemoveRows(parent_index, row, row);
    data_.erase(std::next(data_.begin(), row));
    endRemoveRows();
}

void CardTableItemModel::purgeInactive() {
    beginResetModel();
    std::erase_if(data_, [](auto const &card) { return !card.active(); });
    endResetModel();
}
