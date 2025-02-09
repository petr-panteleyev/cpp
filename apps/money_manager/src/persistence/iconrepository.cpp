//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "iconrepository.h"

IconRepository::IconRepository() : Repository{"icon"} {
}

Icon IconRepository::fromResultSet(const ResultSet &rs) const {
    return Icon(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQByteArray("bytes"), rs.getLong("created"),
                rs.getLong("modified"));
}

void IconRepository::fromResultSet(const ResultSet &rs, std::vector<Icon> &result) const {
    result.emplace_back(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQByteArray("bytes"), rs.getLong("created"),
                        rs.getLong("modified"));
}
