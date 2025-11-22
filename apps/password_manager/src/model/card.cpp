//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "card.hpp"

Card::Card(const CardClass &cardClass, const UUID::UUID &uuid, const Picture &picture, const std::u16string &name,
           unsigned long modified, const std::u16string &note, bool favorite, bool active,
           const std::vector<Field> &fields)
    : cardClass_{cardClass}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
      favorite_{favorite}, active_{active}, fields_{fields} {
}

Card::Card(const UUID::UUID &uuid, const Picture &picture, const std::u16string &name, unsigned long modified,
           const std::u16string &note, bool favorite, bool active, const std::vector<Field> &fields)
    : Card(CardClass::CARD, uuid, picture, name, modified, note, favorite, active, fields) {
}

Card::Card(const Picture &picture, const std::u16string &name, unsigned long modified, const std::vector<Field> &fields)
    : Card(CardClass::CARD, UUID::randomUuid(), picture, name, modified, u"", false, true, fields) {
}

Card::Card(const UUID::UUID &uuid, const std::u16string &name, unsigned long modified, const std::u16string &note,
           bool favorite, bool active)
    : Card(CardClass::NOTE, uuid, Picture::NOTE, name, modified, note, favorite, active, {}) {
}

Card::Card(const std::u16string &name, unsigned long modified)
    : Card(CardClass::NOTE, UUID::randomUuid(), Picture::NOTE, name, modified, u"", false, true, {}) {
}

Card::Card() : Card(u"", 0) {
}

bool Card::operator==(const Card &that) const noexcept {
    return this->cardClass_.get() == that.cardClass_.get() && this->uuid_ == that.uuid_ &&
           this->picture_.get() == that.picture_.get() && this->name_ == that.name_ &&
           this->modified_ == that.modified_ && this->note_ == that.note_ && this->favorite_ == that.favorite_ &&
           this->active_ == that.active_ && this->fields_ == that.fields_;
}
