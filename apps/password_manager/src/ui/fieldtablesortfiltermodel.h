//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QSortFilterProxyModel>

class FieldTableSortFilterModel : public QSortFilterProxyModel {
  public:
    explicit FieldTableSortFilterModel(QObject *parent) : QSortFilterProxyModel{parent} {}

    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};
