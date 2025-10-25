//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "enumclass.h"
#include "field.h"
#include "picture.h"
#include <QString>

class RecordType;
using RecordTypeRef = std::reference_wrapper<const RecordType>;

class RecordType final : public Common::EnumClass<RecordType> {
  public:
    static const RecordType EMPTY;
    static const RecordType CREDIT_CARD;
    static const RecordType PASSWORD;

  public:
    const Picture &picture() const noexcept { return picture_; }
    const QString &translation() const noexcept { return translation_; }
    const std::vector<Field> &fields() const noexcept { return fields_; }

  private:
    explicit RecordType(const std::string &name, const Picture &picture, const QString &translation,
                        const std::vector<Field> &&fields) noexcept
        : EnumClass{name}, picture_{picture}, translation_{translation}, fields_{fields} {}

  private:
    const Picture &picture_;
    QString translation_;
    std::vector<Field> fields_;
};
