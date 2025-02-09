//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "fieldtablesortfiltermodel.h"
#include "field.h"
#include "fieldtableitemmodel.h"

bool FieldTableSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto model = reinterpret_cast<FieldTableItemModel *>(sourceModel());
    return !model->fieldAtIndex(sourceRow)->isEmpty();
}
