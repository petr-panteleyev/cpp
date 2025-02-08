//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "iconrepository.h"

IconRepository::IconRepository() : Repository{"icon"} {
}

std::unique_ptr<Icon> IconRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_unique<Icon>(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQByteArray("bytes"),
                                  rs.getLong("created"), rs.getLong("modified"));
}
