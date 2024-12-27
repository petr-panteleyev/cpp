//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDTABLESORTFILTERMODEL_H
#define CARDTABLESORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class CardTableSortFilterModel : public QSortFilterProxyModel {
  public:
    explicit CardTableSortFilterModel(QObject *parent)
        : QSortFilterProxyModel{parent}, showDeleted_{false} {};

    void setShowDeleted(bool show_deleted) {
        showDeleted_ = show_deleted;
        invalidateRowsFilter();
    }

    void setFilterText(const QString &filterText) {
        filterText_ = filterText;
        invalidateRowsFilter();
    }

    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

  private:
    bool showDeleted_;
    QString filterText_;
};

#endif // CARDTABLESORTFILTERMODEL_H
