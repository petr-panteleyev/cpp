//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "account.h"
#include "repository.h"

class AccountRepository final : public Repository<Account> {
  public:
    AccountRepository();
    ~AccountRepository() = default;

  protected:
    virtual Account fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Account> &result) const override;
};
