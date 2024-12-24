//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTRECORDTABLEMODEL_H
#define IMPORTRECORDTABLEMODEL_H

#include "importrecord.h"
#include <QAbstractItemModel>

class ImportRecordTableModel final : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int COLUMN_TITLE = 0;
    static constexpr int COLUMN_UPDATED = 1;
    static constexpr int COLUMN_ACTION = 2;

  public:
    explicit ImportRecordTableModel(QObject *parent = nullptr);
    ~ImportRecordTableModel();

    void setItems(const ImportRecordVec data) {
        beginResetModel();
        data_ = data;
        endResetModel();
    }

    void toggleApproval(int row);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return parentIndex_; }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return data_.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    const ImportRecordPtr &at(int row) const { return data_.at(row); }

  private:
    ImportRecordVec data_;

    static inline QModelIndex parentIndex_;
};

#endif // IMPORTRECORDTABLEMODEL_H
