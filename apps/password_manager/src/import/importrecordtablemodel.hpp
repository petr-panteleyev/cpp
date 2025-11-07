//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "importrecord.hpp"
#include <QAbstractItemModel>

class ImportRecordTableModel final : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int COLUMN_TITLE = 0;
    static constexpr int COLUMN_UPDATED = 1;
    static constexpr int COLUMN_ACTION = 2;

  public:
    explicit ImportRecordTableModel(QObject *parent);
    ~ImportRecordTableModel();

    void setRecords(const std::vector<ImportRecord> &records) {
        beginResetModel();
        records_ = records;
        endResetModel();
    }

    const std::vector<ImportRecord> records() const { return records_; }

    void toggleApproval(int row);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return QModelIndex(); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return records_.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    ImportRecord *at(int row) const { return const_cast<ImportRecord *>(std::next(records_.data(), row)); }

  private:
    std::vector<ImportRecord> records_;
};
