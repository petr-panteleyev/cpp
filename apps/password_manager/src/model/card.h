/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARD_H
#define CARD_H

#include "cardclass.h"
#include "field.h"
#include "picture.h"
#include <QUuid>
#include <vector>

class Card final {
  public:
    Card(const CardClass &cardClass, const QUuid &uuid, const Picture &picture, const QString &name,
         unsigned long modified, const QString &note, bool favorite, bool active, const std::vector<FieldPtr> &fields)
        : cardClass_{cardClass}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
          favorite_{favorite}, active_{active}, fields_{fields} {}

    Card(const QUuid &uuid, const Picture &picture, const QString &name, unsigned long modified, const QString &note,
         bool favorite, bool active, const std::vector<FieldPtr> &fields)
        : cardClass_{CardClass::CARD}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
          favorite_{favorite}, active_{active}, fields_{fields} {}

    Card(const Picture &picture, const QString &name, unsigned long modified, const std::vector<FieldPtr> &fields)
        : cardClass_{CardClass::CARD}, uuid_{QUuid::createUuid()}, picture_{picture}, name_{name}, modified_{modified},
          note_{""}, favorite_{false}, active_{true}, fields_{fields} {}

    Card(const QUuid &uuid, const QString &name, unsigned long modified, const QString &note, bool favorite,
         bool active)
        : cardClass_{CardClass::NOTE}, uuid_{uuid}, picture_{Picture::NOTE}, name_{name}, modified_{modified},
          note_{note}, favorite_{favorite}, active_{active}, fields_{} {}

    Card(const QString &name, unsigned long modified)
        : cardClass_{CardClass::NOTE}, uuid_{QUuid::createUuid()}, picture_{Picture::NOTE}, name_{name},
          modified_{modified}, note_{""}, favorite_{false}, active_{true}, fields_{} {}

    explicit Card(const Card &card);

  public:
    const CardClass             &cardClass() const { return cardClass_; }
    const QUuid                 &uuid() const { return uuid_; }
    const Picture               &picture() const { return picture_; }
    const QString               &name() const { return name_; }
    const QString               &note() const { return note_; }
    bool                         favorite() const { return favorite_; }
    bool                         active() const { return active_; }
    unsigned long                modified() const { return modified_; }
    const std::vector<FieldPtr> &fields() const { return fields_; }

    void setPicture(const Picture &picture) { picture_ = picture; }
    void setName(const QString &name) { name_ = name; }
    void setNote(const QString &note) { note_ = note; }
    void setActive(bool active) { active_ = active; }
    void setFields(const std::vector<FieldPtr> &fields) { fields_ = fields; }
    void toggleFavorite() noexcept { favorite_ = !favorite_; }
    void toggleActive() noexcept { active_ = !active_; }

    bool isCard() const noexcept { return cardClass_ == CardClass::CARD; }
    bool isNote() const noexcept { return cardClass_ == CardClass::NOTE; }

  private:
    const CardClass      &cardClass_;
    QUuid                 uuid_;
    PictureRef            picture_;
    QString               name_;
    unsigned long         modified_;
    QString               note_;
    bool                  favorite_;
    bool                  active_;
    std::vector<FieldPtr> fields_;
};

using CardPtr = std::shared_ptr<Card>;

#endif // CARD_H
