//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDTABLEITEMMODEL_H
#define CARDTABLEITEMMODEL_H

#include "card.h"
#include <QAbstractItemModel>

class CardTableItemModel : public QAbstractItemModel {
  public:
    static constexpr int ICON_COLUMN = 0;
    static constexpr int NAME_COLUMN = 1;
    static constexpr int AUX_COLUMN = 2;

  public:
    explicit CardTableItemModel(QObject *parent) : QAbstractItemModel{parent} {};

    void setItems(std::vector<Card> &items) {
        beginResetModel();
        data_ = items;
        endResetModel();
    }

    void clearItems() {
        beginResetModel();
        data_.clear();
        endResetModel();
    }

    virtual int columnCount(const QModelIndex &parent) const override { return 3; }
    virtual QModelIndex parent(const QModelIndex &parent) const override { return parent_index; }
    virtual int rowCount(const QModelIndex &parent) const override { return data_.size(); }
    int rowCount() const { return data_.size(); }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override {
        return createIndex(row, column);
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Card &cardAtIndex(int index) { return data_.at(index); }

    void cardUpdated(int row) { emit dataChanged(createIndex(row, 0), createIndex(row, 2)); }
    void replace(int row, const Card &card);
    void addOrReplace(const Card &card);
    void add(const Card &card);
    void deleteCard(int row);
    void purgeInactive();

    const std::vector<Card> &data() const noexcept { return data_; }

  private:
    static inline const QModelIndex parent_index = QModelIndex();

    std::vector<Card> data_;
};

#endif // CARDTABLEITEMMODEL_H
