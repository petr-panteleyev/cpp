/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "model/card.h"
#include <QDomDocument>
#include <vector>

namespace Serializer {

void deserialize(const QDomDocument &doc, std::vector<CardPtr> &list);

} // namespace Serializer

#endif // SERIALIZER_H
