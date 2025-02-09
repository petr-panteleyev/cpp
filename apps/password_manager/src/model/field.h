//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include <QVariant>

class FieldType;

class Field final {
  public:
    explicit Field(const FieldType &type, const QString &name, const QVariant &value) noexcept;
    explicit Field(const Field &f) noexcept = default;
    Field(Field &&) = default;
    ~Field() = default;

    Field &operator=(const Field &) noexcept = default;

    const FieldType &type() const noexcept { return type_; }
    const QString &name() const noexcept { return name_; }
    const QVariant &value() const noexcept { return value_; }

    void setType(const FieldType &type) noexcept { type_ = type; }
    void setName(const QString &name) noexcept { name_ = name; }
    void setValue(const QVariant &value) noexcept { value_ = value; }

    bool showContent() const noexcept { return showContent_; }
    void toggleShow() noexcept;

    [[nodiscard]] QVariant convertValue(const FieldType &newType) const noexcept;

    QString getValueAsString() const;

    bool isEmpty() const { return getValueAsString().isEmpty(); }

    static QVariant deserialize(const QString &str, const FieldType &type);

  private:
    std::reference_wrapper<const FieldType> type_;
    QString name_;
    QVariant value_;

    bool showContent_;
};

#endif // FIELD_H
