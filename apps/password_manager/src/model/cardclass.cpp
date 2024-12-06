/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardclass.h"
#include <stdexcept>

const CardClass &CardClass::valueOf(const std::string &name) {
    for (const CardClass &cardClass : values_) {
        if (cardClass.name() == name) {
            return cardClass;
        }
    }
    throw std::out_of_range("CardClass::" + name + " is not defined");
}
