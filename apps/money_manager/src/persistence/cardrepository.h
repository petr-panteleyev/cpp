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
    virtual Card fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Card> &result) const override;
};

#endif // CARDREPOSITORY_H
