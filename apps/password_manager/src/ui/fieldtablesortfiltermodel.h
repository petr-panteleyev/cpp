/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef FIELDTABLESORTFILTERMODEL_H
#define FIELDTABLESORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class FieldTableSortFilterModel : public QSortFilterProxyModel {
  public:
    explicit FieldTableSortFilterModel(QObject *parent = nullptr) : QSortFilterProxyModel{parent} {}

    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // FIELDTABLESORTFILTERMODEL_H
