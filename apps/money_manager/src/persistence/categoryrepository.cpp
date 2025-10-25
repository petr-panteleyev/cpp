//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "categoryrepository.h"

CategoryRepository::CategoryRepository() : Repository{"category"} {
}

Category CategoryRepository::fromResultSet(const ResultSet &rs) const {
    return Category(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQString("comment"),
                    rs.getEnum<CategoryType>("type"), rs.getNullableQUuid("icon_uuid"), rs.getLong("created"),
                    rs.getLong("modified"));
}

void CategoryRepository::fromResultSet(const ResultSet &rs, std::vector<Category> &result) const {
    result.emplace_back(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQString("comment"),
                        rs.getEnum<CategoryType>("type"), rs.getNullableQUuid("icon_uuid"), rs.getLong("created"),
                        rs.getLong("modified"));
}
