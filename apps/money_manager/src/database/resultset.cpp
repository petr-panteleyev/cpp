//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "resultset.h"
#include "sqlexception.h"
#include <QSqlQuery>
#include <vector>

using Common::Decimal;

ResultSet::ResultSet(const std::shared_ptr<QSqlQuery> &query) noexcept : query_{query}, currentRow_{-1} {
    rows_ = query->size();
}

ResultSet::~ResultSet() {
}

bool ResultSet::next() noexcept {
    return query_->next();
}

std::string ResultSet::getString(int columnNumber) const {
    return query_->value(columnNumber).toString().toStdString();
}

std::string ResultSet::getString(const QString &name) const {
    return query_->value(name).toString().toStdString();
}

QString ResultSet::getQString(int columnNumber) const {
    return query_->value(columnNumber).toString();
}

QString ResultSet::getQString(const QString &name) const {
    return query_->value(name).toString();
}

QUuid ResultSet::getQUuid(int columnNumber) const {
    return query_->value(columnNumber).toUuid();
}

QUuid ResultSet::getQUuid(const QString &name) const {
    auto value = query_->value(name);
    return query_->value(name).toUuid();
}

std::optional<QUuid> ResultSet::getNullableQUuid(int columnNumber) const {
    auto value = query_->value(columnNumber);
    return value.isNull() ? std::nullopt : std::optional(value.toUuid());
}

std::optional<QUuid> ResultSet::getNullableQUuid(const QString &name) const {
    auto value = query_->value(name);
    return value.isNull() ? std::nullopt : std::optional(value.toUuid());
}

long ResultSet::getLong(int columnNumber) const {
    return query_->value(columnNumber).toLongLong();
}

long ResultSet::getLong(const QString &name) const {
    return query_->value(name).toLongLong();
}

std::optional<long> ResultSet::getNullableLong(int columnNumber) const {
    auto value = query_->value(columnNumber);
    return value.isNull() ? std::nullopt : std::optional(value.toLongLong());
}

std::optional<long> ResultSet::getNullableLong(const QString &name) const {
    auto value = query_->value(name);
    return value.isNull() ? std::nullopt : std::optional(value.toLongLong());
}

int ResultSet::getInt(int columnNumber) const {
    return query_->value(columnNumber).toInt();
}

int ResultSet::getInt(const QString &name) const {
    return query_->value(name).toInt();
}

bool ResultSet::getBoolean(int columnNumber) const {
    return query_->value(columnNumber).toBool();
}

bool ResultSet::getBoolean(const QString &name) const {
    return query_->value(name).toBool();
}

Decimal ResultSet::getDecimal(int columnNumber) const {
    auto str = getQString(columnNumber);
    return Decimal(str.toStdString());
}

Decimal ResultSet::getDecimal(const QString &name) const {
    auto str = getQString(name);
    return Decimal(str.toStdString());
}

QDate ResultSet::getQDate(int columnNumber) const {
    return query_->value(columnNumber).toDate();
}

QDate ResultSet::getQDate(const QString &name) const {
    return query_->value(name).toDate();
}

std::optional<QDate> ResultSet::getNullableQDate(int columnNumber) const {
    auto value = query_->value(columnNumber);
    return value.isNull() ? std::nullopt : std::optional(value.toDate());
}

std::optional<QDate> ResultSet::getNullableQDate(const QString &name) const {
    auto value = query_->value(name);
    return value.isNull() ? std::nullopt : std::optional(value.toDate());
}

std::vector<std::byte> ResultSet::getBytes(int columnNumber) const {
    return std::vector<std::byte>();

    //    assert(pgResult_ != nullptr);
    //    assert(columnNumber >= 0 && columnNumber < columns_);

    //    int length = PQgetlength(pgResult_, currentRow_, columnNumber);
    //    if (length <= 0) {
    //        throw SqlException("Binary size <= 0");
    //    }

    //    std::vector<std::byte> result;
    //    result.resize(length);

    //    char *bytes = getValue(pgResult_, currentRow_, columnNumber);
    //    std::memcpy(result.data(), bytes, length);
    //    return result;
}

std::vector<std::byte> ResultSet::getBytes(const QString &name) const {
    return std::vector<std::byte>();
    //    return getBytes(getColumnNumber(name));
}
