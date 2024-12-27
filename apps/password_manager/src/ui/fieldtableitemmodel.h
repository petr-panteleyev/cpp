//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef FIELDTABLEITEMMODEL_H
#define FIELDTABLEITEMMODEL_H

#include <QAbstractItemModel>

class Field;

class FieldTableItemModel : public QAbstractItemModel {
  public:
    explicit FieldTableItemModel(QObject *parent) : QAbstractItemModel{parent} {};

    void setItems(const std::vector<std::shared_ptr<Field>> &items) {
        beginResetModel();
        items_ = items;
        endResetModel();
    }

    virtual int columnCount(const QModelIndex &parent) const override { return 2; }
    virtual QModelIndex parent(const QModelIndex &parent) const override { return parent_index; }
    virtual int rowCount(const QModelIndex &parent) const override { return items_.size(); }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override {
        return createIndex(row, column);
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    const std::shared_ptr<Field> fieldAtIndex(int index) const { return items_.at(index); }

    void toggleMasking(const QModelIndex &index, const std::shared_ptr<Field> &field);

  private:
    static inline const QModelIndex parent_index = QModelIndex();

    std::vector<std::shared_ptr<Field>> items_;
};

#endif // FIELDTABLEITEMMODEL_H
