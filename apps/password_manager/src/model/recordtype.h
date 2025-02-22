//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef RECORDTYPE_H
#define RECORDTYPE_H

#include "enumclass.h"
#include "field.h"
#include "picture.h"

class RecordType;
using RecordTypeRef = std::reference_wrapper<const RecordType>;

class RecordType final : public Common::EnumClass<RecordType> {
  public:
    static const RecordType EMPTY;
    static const RecordType CREDIT_CARD;
    static const RecordType PASSWORD;

  public:
    const Picture &picture() const noexcept { return picture_; }
    const std::vector<Field> &fields() const noexcept { return fields_; }

  private:
    explicit RecordType(const std::string &name, const Picture &picture, const std::vector<Field> &&fields) noexcept
        : EnumClass{name}, picture_{picture}, fields_{fields} {}

  private:
    const Picture &picture_;
    std::vector<Field> fields_;
};

#endif // RECORDTYPE_H
