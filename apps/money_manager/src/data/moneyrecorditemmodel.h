//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MONEYRECORDITEMMODE_H
#define MONEYRECORDITEMMODE_H

#include <QAbstractItemModel>

class MoneyRecord;

class MoneyRecordItemModel final : public QAbstractItemModel {
    friend class DataCacheImpl;
    friend class DataCache;

  public:
    explicit MoneyRecordItemModel() : size_{0} {};
    ~MoneyRecordItemModel() = default;

    void setSize(int size) noexcept { size_ = size; }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return QModelIndex(); };
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override { return QVariant(); };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return size_; };
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 100; };

  private:
    int size_;
};

#endif // MONEYRECORDITEMMODE_H
