//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "card.h"
#include "field.h"

Card::Card(const CardClass &cardClass, const QUuid &uuid, const Picture &picture, const QString &name,
           unsigned long modified, const QString &note, bool favorite, bool active,
           const std::vector<std::shared_ptr<Field>> &fields)
    : cardClass_{cardClass}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
      favorite_{favorite}, active_{active}, fields_{fields} {
}

Card::Card(const QUuid &uuid, const Picture &picture, const QString &name, unsigned long modified, const QString &note,
           bool favorite, bool active, const std::vector<std::shared_ptr<Field>> &fields)
    : Card(CardClass::CARD, uuid, picture, name, modified, note, favorite, active, fields) {
}

Card::Card(const Picture &picture, const QString &name, unsigned long modified,
           const std::vector<std::shared_ptr<Field>> &fields)
    : Card(CardClass::CARD, QUuid::createUuid(), picture, name, modified, "", false, true, fields) {
}

Card::Card(const QUuid &uuid, const QString &name, unsigned long modified, const QString &note, bool favorite,
           bool active)
    : Card(CardClass::NOTE, uuid, Picture::NOTE, name, modified, note, favorite, active, {}) {
}

Card::Card(const QString &name, unsigned long modified)
    : Card(CardClass::NOTE, QUuid::createUuid(), Picture::NOTE, name, modified, "", false, true, {}) {
}

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

Card::~Card() {
}
