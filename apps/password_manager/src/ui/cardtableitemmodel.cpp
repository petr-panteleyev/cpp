/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardtableitemmodel.h"
#include <memory>

static QVariant build_aux_icon_value(const Card &card) {
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

QVariant CardTableItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || (std::size_t)index.row() >= data_.size()) {
        return QVariant();
    }

    auto card = data_.at(index.row());

    switch (index.column()) {
        case 0: return role == Qt::DecorationRole ? card->picture().icon() : QVariant();
        case 1: return role == Qt::DisplayRole ? card->name() : QVariant();
        case 2: return role == Qt::DecorationRole ? build_aux_icon_value(*card) : QVariant();
        default: return QVariant();
    }
}

void CardTableItemModel::replace(const QModelIndex &index, const Card &card) {
    data_[index.row()] = std::make_shared<Card>(card);
    emit dataChanged(index, index);
}

void CardTableItemModel::add(const CardPtr &card) {
    beginInsertRows(parent_index, data_.size(), data_.size());
    data_.push_back(card);
    endInsertRows();
}

void CardTableItemModel::deleteCard(const QModelIndex &index) {
    beginRemoveRows(parent_index, index.row(), index.row());
    data_.erase(std::next(data_.begin(), index.row()));
    endRemoveRows();
}

void CardTableItemModel::purgeInactive() {
    beginResetModel();
    data_.erase(std::remove_if(data_.begin(), data_.end(), [](auto const &card) { return !card->active(); }),
                data_.end());
    endResetModel();
}
