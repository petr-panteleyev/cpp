//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "currencyrepository.h"

CurrencyRepository::CurrencyRepository() : Repository{"currency"} {
}

Currency CurrencyRepository::fromResultSet(const ResultSet &rs) const {
    return Currency(rs.getQUuid("uuid"), rs.getQString("symbol"), rs.getQString("description"),
                    rs.getQString("format_symbol"), rs.getInt("format_symbol_pos"), rs.getBoolean("show_format_symbol"),
                    rs.getBoolean("def"), rs.getDecimal("rate"), rs.getInt("rate_direction"),
                    rs.getBoolean("use_th_separator"), rs.getLong("created"), rs.getLong("modified"));
}

void CurrencyRepository::fromResultSet(const ResultSet &rs, std::vector<Currency> &result) const {
    result.emplace_back(rs.getQUuid("uuid"), rs.getQString("symbol"), rs.getQString("description"),
                        rs.getQString("format_symbol"), rs.getInt("format_symbol_pos"),
                        rs.getBoolean("show_format_symbol"), rs.getBoolean("def"), rs.getDecimal("rate"),
                        rs.getInt("rate_direction"), rs.getBoolean("use_th_separator"), rs.getLong("created"),
                        rs.getLong("modified"));
}
