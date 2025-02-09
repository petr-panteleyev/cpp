//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CURRENCYREPOSITORY_H
#define CURRENCYREPOSITORY_H

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

#endif // CURRENCYREPOSITORY_H
