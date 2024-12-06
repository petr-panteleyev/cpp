/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "fieldtype.h"
#include <stdexcept>

const FieldType &FieldType::valueOf(const std::string &name) {
    for (const FieldType &fieldType : values_) {
        if (fieldType.name() == name) {
            return fieldType;
        }
    }
    throw std::out_of_range("FieldType::" + name + " not defined");
}
