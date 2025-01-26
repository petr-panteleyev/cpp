//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MONEYRECORDITEMMODE_H
#define MONEYRECORDITEMMODE_H

#include <QAbstractItemModel>

class MoneyRecord;

template <class R>
    requires std::derived_from<R, MoneyRecord>
class MoneyRecordItemModel final : public QAbstractItemModel {
    friend class DataCacheImpl;

  public:
    explicit MoneyRecordItemModel(const std::vector<std::shared_ptr<R>> &data) : data_{data} {};
    ~MoneyRecordItemModel() = default;

    QModelIndex index(int row, int column, const QModelIndex &parent = TOP_LEVEL) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return TOP_LEVEL; };
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override { return QVariant(); };

    int rowCount(const QModelIndex &parent = TOP_LEVEL) const override { return data_.size(); };
    int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 100; };

  private:
    const std::vector<std::shared_ptr<R>> &data_;
    static inline QModelIndex TOP_LEVEL = QModelIndex();
};

#endif // MONEYRECORDITEMMODE_H
