//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "categoryrepository.h"

CategoryRepository::CategoryRepository() : Repository{"category"} {
}

std::shared_ptr<Category> CategoryRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_shared<Category>(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQString("comment"),
                                      rs.getEnum<CategoryType>("type"), rs.getNullableQUuid("icon_uuid"),
                                      rs.getLong("created"), rs.getLong("modified"));
}
