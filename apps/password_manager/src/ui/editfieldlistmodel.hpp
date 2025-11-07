//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "field.hpp"
#include <QAbstractItemModel>

class EditFieldListModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int FIELD_TABLE_NAME_COLUMN = 0;
    static constexpr int FIELD_TABLE_TYPE_COLUMN = 1;
    static constexpr int FIELD_TABLE_VALUE_COLUMN = 2;

  public:
    explicit EditFieldListModel(QObject *parent);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return QModelIndex(); };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return fields_.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void setFields(const std::vector<Field> &fields);
    const std::vector<Field> &fields() const { return fields_; }

    Field *at(int row) const { return const_cast<Field *>(std::next(fields_.data(), row)); }

    void addField();
    void deleteField(int row);
    void moveUp(int row);
    void moveDown(int row);
    void setFieldValue(int row, const QVariant &value);

  private:
    std::vector<Field> fields_;
};
