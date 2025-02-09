//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardrepository.h"

CardRepository::CardRepository() : Repository{"card"} {
}

Card CardRepository::fromResultSet(const ResultSet &rs) const {
    return Card(rs.getQUuid("uuid"), rs.getQUuid("account_uuid"), rs.getEnum<CardType>("type"), rs.getQString("number"),
                rs.getQDate("expiration"), rs.getQString("comment"), rs.getBoolean("enabled"), rs.getLong("created"),
                rs.getLong("modified"));
}

void CardRepository::fromResultSet(const ResultSet &rs, std::vector<Card> &result) const {
    result.emplace_back(rs.getQUuid("uuid"), rs.getQUuid("account_uuid"), rs.getEnum<CardType>("type"),
                        rs.getQString("number"), rs.getQDate("expiration"), rs.getQString("comment"),
                        rs.getBoolean("enabled"), rs.getLong("created"), rs.getLong("modified"));
}
