/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef EDITFIELDLISTMODEL_H
#define EDITFIELDLISTMODEL_H

#include "field.h"
#include <QAbstractItemModel>

class EditFieldListModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int FIELD_TABLE_NAME_COLUMN = 0;
    static constexpr int FIELD_TABLE_TYPE_COLUMN = 1;
    static constexpr int FIELD_TABLE_VALUE_COLUMN = 2;

  public:
    explicit EditFieldListModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return parentIndex; };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return fields_.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool     setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void               setFields(const FieldVec &fields) { fields_ = fields; }
    const FieldVec &fields() const { return fields_; }

    const FieldPtr &at(int row) const { return fields_.at(row); };

    void addField();
    void deleteField(int row);
    void moveUp(int row);
    void moveDown(int row);

  private:
    static inline const QModelIndex parentIndex = QModelIndex();

    FieldVec fields_;
};

#endif // EDITFIELDLISTMODEL_H
