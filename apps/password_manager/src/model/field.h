/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef FIELD_H
#define FIELD_H

#include "fieldtype.h"
#include <QString>
#include <QVariant>

class Field final {
  public:
    explicit Field(const FieldType &type, const QString &name, const QVariant &value) noexcept
        : type_{type}, name_{name}, value_{value} {
        showContent_ = !type.masked();
    }

    explicit Field(const Field &f) noexcept : Field(f.type(), f.name(), f.value()) {}

    const FieldType &type() const noexcept { return type_; }
    const QString   &name() const noexcept { return name_; }
    const QVariant  &value() const noexcept { return value_; }

    void setType(const FieldType &type) noexcept { type_ = type; }
    void setName(const QString &name) noexcept { name_ = name; }
    void setValue(const QVariant &value) noexcept { value_ = value; }

    bool showContent() const noexcept { return showContent_; }
    void toggleShow() noexcept {
        if (type().masked()) {
            showContent_ = !showContent_;
        }
    }

    [[nodiscard]] QVariant convertValue(const FieldType &newType) const noexcept;

    QString getValueAsString() const;

    bool isEmpty() const { return getValueAsString().isEmpty(); }

    static QVariant deserialize(const QString &str, const FieldType &type);

  private:
    FieldTypeRef type_;
    QString      name_;
    QVariant     value_;

    bool showContent_;
};

using FieldPtr = std::shared_ptr<Field>;
using FieldVec = std::vector<FieldPtr>;

#endif // FIELD_H
