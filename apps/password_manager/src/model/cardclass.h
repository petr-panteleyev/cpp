//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDCLASS_H
#define CARDCLASS_H

#include "enumclass.h"

class CardClass final : public Common::EnumClass<CardClass> {
  public:
    static const CardClass CARD;
    static const CardClass NOTE;

  private:
    explicit CardClass(const std::string &name) noexcept : EnumClass{name} {}
};

#endif // CARDCLASS_H
