//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef RECORDTYPE_H
#define RECORDTYPE_H

#include "enumclass.h"
#include "picture.h"

class Field;
class RecordType;
using RecordTypeRef = std::reference_wrapper<const RecordType>;

class RecordType final : public Common::EnumClass<RecordType> {
  public:
    static const RecordType EMPTY;
    static const RecordType CREDIT_CARD;
    static const RecordType PASSWORD;

  public:
    const Picture &picture() const noexcept { return picture_; }
    const std::vector<std::shared_ptr<Field>> &fields() const noexcept { return fields_; }

  private:
    explicit RecordType(const std::string &name, const Picture &picture, const std::vector<std::shared_ptr<Field>> &fields) noexcept
        : EnumClass{name}, picture_{picture}, fields_{fields} {}

  private:
    const Picture &picture_;
    const std::vector<std::shared_ptr<Field>> fields_;
};

#endif // RECORDTYPE_H
