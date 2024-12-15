/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef FIELDTABLEITEMMODEL_H
#define FIELDTABLEITEMMODEL_H

#include "field.h"
#include <QAbstractItemModel>

class FieldTableItemModel : public QAbstractItemModel {
  public:
    explicit FieldTableItemModel(QObject *parent = nullptr) : QAbstractItemModel{parent} {};

    void setItems(const FieldVec &items) {
        beginResetModel();
        items_ = items;
        endResetModel();
    }

    virtual int         columnCount(const QModelIndex &parent) const override { return 2; }
    virtual QModelIndex parent(const QModelIndex &parent) const override { return parent_index; }
    virtual int         rowCount(const QModelIndex &parent) const override { return items_.size(); }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override {
        return createIndex(row, column);
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    const FieldPtr   fieldAtIndex(int index) const { return items_.at(index); }

    void toggleMasking(const QModelIndex &index, const FieldPtr &field);

  private:
    static inline const QModelIndex parent_index = QModelIndex();

    FieldVec items_;
};

#endif // FIELDTABLEITEMMODEL_H
