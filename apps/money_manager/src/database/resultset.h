//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef RESULTSET_H
#define RESULTSET_H

#include "decimal.h"
#include <QDate>
#include <QString>
#include <QUuid>
#include <optional>
#include <string>
#include <QByteArray>

class QSqlQuery;

class ResultSet final {
  public:
    ResultSet(QSqlQuery &query) noexcept;
    ~ResultSet();

    bool next() noexcept;

    std::string getString(int columnNumber) const;
    std::string getString(const QString &name) const;

    QString getQString(int columnNumber) const;
    QString getQString(const QString &name) const;

    QUuid getQUuid(int columnNumber) const;
    QUuid getQUuid(const QString &name) const;

    std::optional<QUuid> getNullableQUuid(int columnNumber) const;
    std::optional<QUuid> getNullableQUuid(const QString &name) const;

    long getLong(int columnNumber) const;
    long getLong(const QString &name) const;

    std::optional<long> getNullableLong(int columnNumber) const;
    std::optional<long> getNullableLong(const QString &name) const;

    int getInt(int columnNumber) const;
    int getInt(const QString &name) const;

    bool getBoolean(int columnNumber) const;
    bool getBoolean(const QString &name) const;

    Common::Decimal getDecimal(int columnNumber) const;
    Common::Decimal getDecimal(const QString &name) const;

    QDate getQDate(int columnNumber) const;
    QDate getQDate(const QString &name) const;

    std::optional<QDate> getNullableQDate(int columnNumber) const;
    std::optional<QDate> getNullableQDate(const QString &name) const;

    QByteArray getQByteArray(int columnNumber) const;
    QByteArray getQByteArray(const QString &name) const;

    template <class E> const E &getEnum(int columnNumber) const {
        auto stringValue = getString(columnNumber);
        return E::valueOf(stringValue);
    }
    template <class E> const E &getEnum(const QString &name) const {
        auto stringValue = getString(name);
        return E::valueOf(stringValue);
    }

  private:
    QSqlQuery &query_;
    int currentRow_;
    int rows_;
    int columns_;
};

#endif // RESULTSET_H
