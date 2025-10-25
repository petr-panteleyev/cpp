//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "currency.h"
#include "repository.h"

class CurrencyRepository final : public Repository<Currency> {
  public:
    CurrencyRepository();
    ~CurrencyRepository() = default;

  protected:
    virtual Currency fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Currency> &result) const override;
};
