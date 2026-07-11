//  Copyright © 2024-2026 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QSortFilterProxyModel>

class CardTableSortFilterModel : public QSortFilterProxyModel {
  public:
    explicit CardTableSortFilterModel(QObject *parent) : QSortFilterProxyModel{parent}, showDeleted_{false} {};

    void setShowDeleted(bool show_deleted) {
        beginFilterChange();
        showDeleted_ = show_deleted;
        endFilterChange(Direction::Rows);
    }

    void setFilterText(const QString &filterText) {
        beginFilterChange();
        filterText_ = filterText;
        endFilterChange(Direction::Rows);
    }

    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

  private:
    bool showDeleted_;
    QString filterText_;
};
