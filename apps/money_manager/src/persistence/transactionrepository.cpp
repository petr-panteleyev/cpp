//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "transactionrepository.h"
#include "categorytype.h"
#include "transactiontype.h"

TransactionRepository::TransactionRepository() : Repository("transaction") {
}

std::shared_ptr<Transaction> TransactionRepository::fromResultSet(const ResultSet &rs) const {
    return std::make_shared<Transaction>(
        rs.getQUuid("uuid"), rs.getDecimal("amount"), rs.getDecimal("credit_amount"), rs.getQDate("transaction_date"),
        rs.getEnum<TransactionType>("type"), rs.getQString("comment"), rs.getBoolean("checked"),
        rs.getQUuid("acc_debited_uuid"), rs.getQUuid("acc_credited_uuid"), rs.getEnum<CategoryType>("acc_debited_type"),
        rs.getEnum<CategoryType>("acc_credited_type"), rs.getQUuid("acc_debited_category_uuid"),
        rs.getQUuid("acc_credited_category_uuid"), rs.getNullableQUuid("contact_uuid"), rs.getQString("invoice_number"),
        rs.getNullableQUuid("parent_uuid"), rs.getBoolean("detailed"), rs.getQDate("statement_date"),
        rs.getNullableQUuid("card_uuid"), rs.getLong("created"), rs.getLong("modified"));
}
