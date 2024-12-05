/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARDTABLESORTFILTERMODEL_H
#define CARDTABLESORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class CardTableSortFilterModel : public QSortFilterProxyModel {
  public:
    CardTableSortFilterModel() : show_deleted_{false} {};

    void set_show_deleted(bool show_deleted) {
        show_deleted_ = show_deleted;
        invalidateRowsFilter();
    }

    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

  private:
    bool show_deleted_;
};

#endif // CARDTABLESORTFILTERMODEL_H
