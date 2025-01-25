//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>

class CategoryType;
class ContactType;
class TransactionType;

namespace Translation {

const QString &translate(const CategoryType &type);
const QString &translate(const ContactType &type);
const QString &translate(const TransactionType &type);

} // namespace Translation

#endif // TRANSLATION_H
