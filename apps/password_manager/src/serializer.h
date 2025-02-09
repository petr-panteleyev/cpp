//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "card.h"
#include <vector>

class QDomDocument;
class QByteArray;

namespace Serializer {

void deserialize(const QDomDocument &doc, std::vector<Card> &list);
void serialize(const std::vector<Card> &list, QByteArray &byteArray);

} // namespace Serializer

#endif // SERIALIZER_H
