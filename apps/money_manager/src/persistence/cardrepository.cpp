//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardrepository.h"
#include <memory>

CardRepository::CardRepository() : Repository{"card"} {
}

std::unique_ptr<Card> CardRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_unique<Card>(rs.getQUuid("uuid"), rs.getQUuid("account_uuid"), rs.getEnum<CardType>("type"),
                                  rs.getQString("number"), rs.getQDate("expiration"), rs.getQString("comment"),
                                  rs.getBoolean("enabled"), rs.getLong("created"), rs.getLong("modified"));
}
