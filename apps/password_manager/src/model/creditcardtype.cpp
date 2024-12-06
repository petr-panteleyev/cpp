/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "creditcardtype.h"

const CreditCardType &CreditCardType::valueOf(const std::string &name) {
    for (const CreditCardType &type : values_) {
        if (type.name() == name) {
            return type;
        }
    }
    throw std::out_of_range("CreditCardType::" + name + " is not defined");
}
