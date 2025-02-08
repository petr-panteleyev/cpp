//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "categoryrepository.h"

CategoryRepository::CategoryRepository() : Repository{"category"} {
}

std::unique_ptr<Category> CategoryRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_unique<Category>(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQString("comment"),
                                      rs.getEnum<CategoryType>("type"), rs.getNullableQUuid("icon_uuid"),
                                      rs.getLong("created"), rs.getLong("modified"));
}
