//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "contactrepository.h"

ContactRepository::ContactRepository() : Repository{"contact"} {
}

std::shared_ptr<Contact> ContactRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_shared<Contact>(
        rs.getQUuid("uuid"), rs.getQString("name"), rs.getEnum<ContactType>("type"), rs.getQString("phone"),
        rs.getQString("mobile"), rs.getQString("email"), rs.getQString("web"), rs.getQString("comment"),
        rs.getQString("street"), rs.getQString("city"), rs.getQString("country"), rs.getQString("zip"),
        rs.getNullableQUuid("icon_uuid"), rs.getLong("created"), rs.getLong("modified"));
}
