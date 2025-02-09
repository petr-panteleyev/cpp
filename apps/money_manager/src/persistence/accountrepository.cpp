//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "accountrepository.h"

AccountRepository::AccountRepository() : Repository{"account"} {
}

Account AccountRepository::fromResultSet(const ResultSet &rs) const {
    return Account(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQString("comment"), rs.getQString("number"),
                   rs.getDecimal("opening"), rs.getDecimal("account_limit"), rs.getDecimal("rate"),
                   rs.getEnum<CategoryType>("type"), rs.getQUuid("category_uuid"), rs.getNullableQUuid("currency_uuid"),
                   rs.getNullableQUuid("security_uuid"), rs.getBoolean("enabled"), rs.getDecimal("interest"),
                   rs.getNullableQDate("closing_date"), rs.getNullableQUuid("icon_uuid"), rs.getDecimal("total"),
                   rs.getDecimal("total_waiting"), rs.getLong("created"), rs.getLong("modified"));
}

void AccountRepository::fromResultSet(const ResultSet &rs, std::vector<Account> &result) const {
    result.emplace_back(rs.getQUuid("uuid"), rs.getQString("name"), rs.getQString("comment"), rs.getQString("number"),
                        rs.getDecimal("opening"), rs.getDecimal("account_limit"), rs.getDecimal("rate"),
                        rs.getEnum<CategoryType>("type"), rs.getQUuid("category_uuid"),
                        rs.getNullableQUuid("currency_uuid"), rs.getNullableQUuid("security_uuid"),
                        rs.getBoolean("enabled"), rs.getDecimal("interest"), rs.getNullableQDate("closing_date"),
                        rs.getNullableQUuid("icon_uuid"), rs.getDecimal("total"), rs.getDecimal("total_waiting"),
                        rs.getLong("created"), rs.getLong("modified"));
}
