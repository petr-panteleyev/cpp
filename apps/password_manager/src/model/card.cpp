//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "card.h"

Card::Card(const CardClass &cardClass, const QUuid &uuid, const Picture &picture, const QString &name,
           unsigned long modified, const QString &note, bool favorite, bool active, const std::vector<Field> &fields)
    : cardClass_{cardClass}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
      favorite_{favorite}, active_{active}, fields_{fields} {
}

Card::Card(const QUuid &uuid, const Picture &picture, const QString &name, unsigned long modified, const QString &note,
           bool favorite, bool active, const std::vector<Field> &fields)
    : Card(CardClass::CARD, uuid, picture, name, modified, note, favorite, active, fields) {
}

Card::Card(const Picture &picture, const QString &name, unsigned long modified, const std::vector<Field> &fields)
    : Card(CardClass::CARD, QUuid::createUuid(), picture, name, modified, "", false, true, fields) {
}

Card::Card(const QUuid &uuid, const QString &name, unsigned long modified, const QString &note, bool favorite,
           bool active)
    : Card(CardClass::NOTE, uuid, Picture::NOTE, name, modified, note, favorite, active, {}) {
}

Card::Card(const QString &name, unsigned long modified)
    : Card(CardClass::NOTE, QUuid::createUuid(), Picture::NOTE, name, modified, "", false, true, {}) {
}

Card::Card() : Card("", 0) {
}
