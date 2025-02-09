//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>

namespace Translation {

const QString &translateCategoryType(unsigned type);
const QString &translateContactType(unsigned type);
const QString &translateTransactionType(unsigned type);

} // namespace Translation

#endif // TRANSLATION_H
