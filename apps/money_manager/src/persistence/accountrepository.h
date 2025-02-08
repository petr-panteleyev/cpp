//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include "account.h"
#include "repository.h"

class AccountRepository final : public Repository<Account> {
  public:
    AccountRepository();
    ~AccountRepository() = default;

  protected:
    virtual std::unique_ptr<Account> fromResultSet(const ResultSet &rs) const override;
};

#endif // ACCOUNTREPOSITORY_H
