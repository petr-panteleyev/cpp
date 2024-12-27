//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTRECORDTABLEMODEL_H
#define IMPORTRECORDTABLEMODEL_H

#include <QAbstractItemModel>

class ImportRecord;

class ImportRecordTableModel final : public QAbstractItemModel {
    Q_OBJECT

  public:
    static constexpr int COLUMN_TITLE = 0;
    static constexpr int COLUMN_UPDATED = 1;
    static constexpr int COLUMN_ACTION = 2;

  public:
    explicit ImportRecordTableModel(QObject *parent);
    ~ImportRecordTableModel();

    void setItems(const std::vector<std::shared_ptr<ImportRecord>> data) {
        beginResetModel();
        data_ = data;
        endResetModel();
    }

    void toggleApproval(int row);

    QModelIndex index(int row, int column, const QModelIndex &parent = TOP_LEVEL) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return TOP_LEVEL; }

    int rowCount(const QModelIndex &parent = TOP_LEVEL) const override { return data_.size(); }
    int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 3; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    const std::shared_ptr<ImportRecord> &at(int row) const { return data_.at(row); }

  private:
    std::vector<std::shared_ptr<ImportRecord>> data_;

    static constexpr QModelIndex TOP_LEVEL = QModelIndex();
};

#endif // IMPORTRECORDTABLEMODEL_H
