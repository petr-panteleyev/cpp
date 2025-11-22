//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "fieldtype.hpp"
#include <chrono>
#include <variant>

class Field final {
  public:
    using FieldValue = std::variant<std::u16string, std::chrono::year_month_day, unsigned int>;

  public:
    explicit Field(const FieldType &type, const std::u16string &name, const FieldValue &value) noexcept;
    explicit Field(const Field &f) noexcept = default;
    Field(Field &&) = default;
    ~Field() = default;

    Field &operator=(const Field &) noexcept = default;

    bool operator==(const Field &that) const noexcept;

    const FieldType &type() const noexcept { return type_; }
    const std::u16string &name() const noexcept { return name_; }
    const FieldValue &value() const noexcept { return value_; }

    void setType(const FieldType &type) noexcept { type_ = type; };
    void setName(const std::u16string &name) noexcept { name_ = name; }
    void setValue(const FieldValue &value) noexcept { value_ = value; }

    bool showContent() const noexcept { return showContent_; }
    void toggleShow() noexcept;

    bool isEmpty() const;

    // Helper functions to check and get typed values
    bool isDate() const noexcept;
    const std::chrono::year_month_day &valueAsDate() const;
    bool isString() const noexcept;
    const std::u16string &valueAsString() const;

  private:
    FieldTypeRef type_;
    std::u16string name_;
    FieldValue value_;

    bool showContent_;
};
