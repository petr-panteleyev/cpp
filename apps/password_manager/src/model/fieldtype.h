/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef FIELDTYPE_H
#define FIELDTYPE_H

#include <functional>
#include <string>
#include <vector>

class FieldType;
using FieldTypeRef = std::reference_wrapper<const FieldType>;

class FieldType final {
  public:
    static const FieldType STRING;
    static const FieldType HIDDEN;
    static const FieldType EMAIL;
    static const FieldType CREDIT_CARD_NUMBER;
    static const FieldType LINK;
    static const FieldType PIN;
    static const FieldType UNIX_PASSWORD;
    static const FieldType SHORT_PASSWORD;
    static const FieldType LONG_PASSWORD;
    static const FieldType CARD_TYPE;
    static const FieldType DATE;
    static const FieldType EXPIRATION_MONTH;

  public:
    static const FieldType &valueOf(const std::string &name);
    static const FieldType &valueOf(unsigned ordinal) { return values_.at(ordinal); }

    static const std::vector<FieldTypeRef> &values() { return values_; }

  public:
    const std::string &name() const { return name_; }
    unsigned           ordinal() const { return ordinal_; }
    bool               masked() const { return masked_; }

    friend bool operator==(const FieldType &x, const FieldType &y) { return x.ordinal_ == y.ordinal_; }
    friend bool operator!=(const FieldType &x, const FieldType &y) { return x.ordinal_ != y.ordinal_; }

  private:
    FieldType(unsigned ordinal, const std::string &name) : ordinal_{ordinal}, name_{name}, masked_{false} {}
    FieldType(unsigned ordinal, const std::string &name, bool masked)
        : ordinal_{ordinal}, name_{name}, masked_{masked} {}
    FieldType(const FieldType &) = delete;
    FieldType(const FieldType &&) = delete;

  private:
    const unsigned    ordinal_;
    const std::string name_;
    const bool        masked_;

    static const std::vector<FieldTypeRef> values_;
};

#endif // FIELDTYPE_H
