//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QAbstractItemModel>
#include <QUuid>
#include <vector>

class MoneyRecord;

template <class R>
    requires std::derived_from<R, MoneyRecord>
class MoneyRecordItemModel final : public QAbstractItemModel {
  public:
    explicit MoneyRecordItemModel(std::vector<R> &data) : data_{data} {};
    ~MoneyRecordItemModel() = default;

    void clear() {
        beginResetModel();
        data_.clear();
        endResetModel();
    }

    void resetItems(const std::function<void(std::vector<R> &)> &dataSupplier) {
        beginResetModel();
        data_.clear();
        dataSupplier(data_);
        endResetModel();
    }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return QModelIndex(); };
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override { return QVariant(); };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return data_.size(); };
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 100; };

    const R &getRecord(QUuid uuid) {
        auto found = std::find_if(data_.begin(), data_.end(), [&uuid](const auto &r) { return r.uuid() == uuid; });
        if (found == data_.end()) {
            throw std::out_of_range("Record not found");
        }
        return *found;
    }

  private:
    std::vector<R> &data_;
};
