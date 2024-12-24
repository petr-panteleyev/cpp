//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef EDITFIELDLISTMODEL_H
#define EDITFIELDLISTMODEL_H

#include <QAbstractItemModel>

class Field;

class EditFieldListModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int FIELD_TABLE_NAME_COLUMN = 0;
    static constexpr int FIELD_TABLE_TYPE_COLUMN = 1;
    static constexpr int FIELD_TABLE_VALUE_COLUMN = 2;

  public:
    explicit EditFieldListModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = TOP_LEVEL) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return TOP_LEVEL; };

    int rowCount(const QModelIndex &parent = TOP_LEVEL) const override { return fields_.size(); }
    int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void setFields(const std::vector<std::shared_ptr<Field>> &fields) {
        beginResetModel();
        fields_ = fields;
        endResetModel();
    }
    const std::vector<std::shared_ptr<Field>> &fields() const { return fields_; }

    const std::shared_ptr<Field> &at(int row) const { return fields_.at(row); };

    void addField();
    void deleteField(int row);
    void moveUp(int row);
    void moveDown(int row);
    void setFieldValue(int row, const std::shared_ptr<Field> &field, const QVariant &value);

  private:
    static constexpr QModelIndex TOP_LEVEL = QModelIndex();

    std::vector<std::shared_ptr<Field>> fields_;
};

#endif // EDITFIELDLISTMODEL_H
