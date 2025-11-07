//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "fieldtablesortfiltermodel.hpp"
#include "field.hpp"
#include "fieldtableitemmodel.hpp"

bool FieldTableSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto model = reinterpret_cast<FieldTableItemModel *>(sourceModel());
    return !model->fieldAtIndex(sourceRow)->isEmpty();
}
