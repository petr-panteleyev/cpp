//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "iconrepository.h"

IconRepository::IconRepository() : Repository{"icon"} {
}

std::shared_ptr<Icon> IconRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_shared<Icon>(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQByteArray("bytes"),
                                  rs.getLong("created"), rs.getLong("modified"));
}
