//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDCLASS_H
#define CARDCLASS_H

#include "enumclass.h"

class CardClass;
using CardClassRef = std::reference_wrapper<const CardClass>;

class CardClass final : public Common::EnumClass<CardClass> {
  public:
    static const CardClass CARD;
    static const CardClass NOTE;

  private:
    CardClass(const std::string &name) : EnumClass{name} {}
};

#endif // CARDCLASS_H
