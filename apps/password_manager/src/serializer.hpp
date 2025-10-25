//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "card.h"
#include <span>
#include <vector>

namespace Serializer {

void initialize();
void deserialize(const std::span<char> &content, std::vector<Card> &cards);
void serialize(const std::vector<Card> &list, QByteArray &byteArray);

} // namespace Serializer
