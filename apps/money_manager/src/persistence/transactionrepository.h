//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H

#include "repository.h"
#include "transaction.h"

class TransactionRepository final : public Repository<Transaction> {
  public:
    TransactionRepository();
    ~TransactionRepository() = default;

  protected:
    virtual Transaction fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Transaction> &result) const override;
};

#endif // TRANSACTIONREPOSITORY_H
