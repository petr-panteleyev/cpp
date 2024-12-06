/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "fieldtablesortfiltermodel.h"
#include "fieldtableitemmodel.h"

bool FieldTableSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto model = (FieldTableItemModel *)sourceModel();
    auto field = model->fieldAtIndex(sourceRow);
    return !field->isEmpty();
}
