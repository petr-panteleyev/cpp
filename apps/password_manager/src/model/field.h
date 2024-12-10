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
    Field(const FieldType &type, const QString &name, const QVariant &value) : type_{type}, name_{name}, value_{value} {
        showContent_ = !type.masked();
    }

    const FieldType &type() const { return type_; }
    const QString   &name() const { return name_; }
    const QVariant  &value() const { return value_; }

    void setType(const FieldType &type) { type_ = type; }
    void setName(const QString &name) { name_ = name; }
    void setValue(const QVariant &value) { value_ = value; }

    bool showContent() const { return showContent_; }
    void toggleShow() {
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

#endif // FIELD_H
