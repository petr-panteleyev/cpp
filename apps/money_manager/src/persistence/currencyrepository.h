//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
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
    virtual std::shared_ptr<Currency> fromResultSet(const ResultSet &rs) const override;
};

#endif // CURRENCYREPOSITORY_H
