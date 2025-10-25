//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "field.h"
#include <QAbstractItemModel>

class FieldTableItemModel : public QAbstractItemModel {
  public:
    explicit FieldTableItemModel(QObject *parent) : QAbstractItemModel{parent} {};

    void clearItems() { items_.clear(); }
    void setItems(const std::vector<Field> &items);

    virtual int columnCount(const QModelIndex &parent) const override { return 2; }
    virtual QModelIndex parent(const QModelIndex &parent) const override { return parent_index; }
    virtual int rowCount(const QModelIndex &parent) const override { return items_.size(); }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override {
        return createIndex(row, column);
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Field *fieldAtIndex(int index) const { return const_cast<Field *>(std::next(items_.data(), index)); }

    void toggleMasking(const QModelIndex &index, Field &field);

  private:
    static inline const QModelIndex parent_index = QModelIndex();

    std::vector<Field> items_;
};
