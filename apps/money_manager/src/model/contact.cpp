//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "contact.h"

Contact::Contact(QUuid uuid, const QString &name, const ContactType &type, const QString &phone, const QString &mobile,
                 const QString &email, const QString &web, const QString &comment, const QString &street,
                 const QString &city, const QString &country, const QString &zip, const std::optional<QUuid> &iconUuid,
                 long created, long modified)
    : MoneyRecord{uuid, created, modified}, name_{name}, type_{type.ordinal()}, phone_{phone}, mobile_{mobile},
      email_{email}, web_{web}, comment_{comment}, street_{street}, city_{city}, country_{country}, zip_{zip},
      iconUuid_{iconUuid} {
}
