//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <memory>
#include <vector>

class QDomDocument;
class QByteArray;
class Card;

namespace Serializer {

void deserialize(const QDomDocument &doc, std::vector<std::shared_ptr<Card>> &list);
void serialize(const std::vector<std::shared_ptr<Card>> &list, QByteArray &byteArray);

} // namespace Serializer

#endif // SERIALIZER_H
