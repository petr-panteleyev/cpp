//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDREPOSITORY_H
#define CARDREPOSITORY_H

#include "card.h"
#include "repository.h"

class CardRepository final : public Repository<Card> {
  public:
    CardRepository();
    ~CardRepository() = default;

  protected:
    virtual std::shared_ptr<Card> fromResultSet(const ResultSet &rs) const override;
};

#endif // CARDREPOSITORY_H
