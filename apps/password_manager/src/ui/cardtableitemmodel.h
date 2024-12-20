/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARDTABLEITEMMODEL_H
#define CARDTABLEITEMMODEL_H

#include "card.h"
#include <QAbstractItemModel>

class CardTableItemModel : public QAbstractItemModel {
  public:
    explicit CardTableItemModel(QObject *parent = nullptr) : QAbstractItemModel{parent} {};

    void setItems(const CardVec &items) {
        beginResetModel();
        data_ = items;
        endResetModel();
    }

    virtual int         columnCount(const QModelIndex &parent) const override { return 3; }
    virtual QModelIndex parent(const QModelIndex &parent) const override { return parent_index; }
    virtual int         rowCount(const QModelIndex &parent) const override { return data_.size(); }
    int                 rowCount() const { return data_.size(); }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override {
        return createIndex(row, column);
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    const CardPtr    cardAtIndex(int index) const { return data_.at(index); }

    void replace(int row, const CardPtr &card);
    void addOrReplace(const CardPtr &card);
    void add(const CardPtr &card);
    void deleteCard(int row);
    void purgeInactive();

    const CardVec &data() const noexcept { return data_; }

  private:
    static inline const QModelIndex parent_index = QModelIndex();

    CardVec data_;
};

#endif // CARDTABLEITEMMODEL_H
