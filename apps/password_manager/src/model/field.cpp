//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "field.hpp"
#include "fieldtype.hpp"

namespace {

constexpr std::size_t VARIANT_STRING = 0;
constexpr std::size_t VARIANT_DATE = VARIANT_STRING + 1;
[[maybe_unused]] constexpr std::size_t VARIANT_UINT = VARIANT_DATE + 1;

} // namespace

Field::Field(const FieldType &type, const std::u16string &name, const FieldValue &value) noexcept
    : type_{type}, name_{name}, value_{value}, showContent_{!type.masked()} {
}

bool Field::operator==(const Field &that) const noexcept {
    return this->type_.get() == that.type_.get() && this->name_ == that.name_ && this->value_ == that.value_;
}

void Field::toggleShow() noexcept {
    if (type().masked()) {
        showContent_ = !showContent_;
    }
}

bool Field::isEmpty() const {
    return value_.index() == VARIANT_STRING ? std::get<std::u16string>(value_).empty() : false;
}

bool Field::isDate() const noexcept {
    return value_.index() == VARIANT_DATE;
}

const std::chrono::year_month_day &Field::valueAsDate() const {
    return std::get<std::chrono::year_month_day>(value_);
}

bool Field::isString() const noexcept {
    return value_.index() == VARIANT_STRING;
}

const std::u16string &Field::valueAsString() const {
    return std::get<std::u16string>(value_);
}
