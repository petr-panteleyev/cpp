//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONTACT_H
#define CONTACT_H

#include "contacttype.h"
#include "moneyrecord.h"
#include <QString>
#include <QUuid>
#include <optional>

class Contact final : public MoneyRecord {
  public:
    Contact(QUuid uuid, const QString &name, const ContactType &type, const QString &phone, const QString &mobile,
            const QString &email, const QString &web, const QString &comment, const QString &street,
            const QString &city, const QString &country, const QString &zip, const std::optional<QUuid> &iconUuid,
            long created, long modified);
    ~Contact() = default;

    const QString &name() const noexcept { return name_; }
    unsigned type() const noexcept { return type_; }
    const QString &phone() const noexcept { return phone_; }
    const QString &email() const noexcept { return email_; }
    std::optional<QUuid> iconUuid() const noexcept { return iconUuid_; }

  private:
    QString name_;
    unsigned type_;
    QString phone_;
    QString mobile_;
    QString email_;
    QString web_;
    QString comment_;
    QString street_;
    QString city_;
    QString country_;
    QString zip_;
    std::optional<QUuid> iconUuid_;
};

#endif // CONTACT_H
