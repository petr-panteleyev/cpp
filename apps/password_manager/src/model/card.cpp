/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "card.h"

Card::Card(const Card &card)
    : cardClass_{card.cardClass_}, uuid_{card.uuid_}, picture_{card.picture_}, name_{card.name_},
      modified_{card.modified_}, note_{card.note_}, favorite_{card.favorite_}, active_{card.active_} {

    // copy fields
    fields_.reserve(card.fields_.size());
    for (const auto &field : card.fields_) {
        auto fieldCopy = std::make_shared<Field>(field->type(), field->name(), field->value());
        fields_.push_back(fieldCopy);
    }
}
