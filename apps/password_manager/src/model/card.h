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
    Card(const CardClass &cardClass, const QUuid &uuid, const Picture &picture, const QString &name, long modified,
         const QString &note, bool favorite, bool active, const std::vector<FieldPtr> &fields)
        : cardClass_{cardClass}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
          favorite_{favorite}, active_{active}, fields_{fields} {}

    Card(const QUuid &uuid, const Picture &picture, const QString &name, long modified, const QString &note,
         bool favorite, bool active, const std::vector<FieldPtr> &fields)
        : cardClass_{CardClass::CARD}, uuid_{uuid}, picture_{picture}, name_{name}, modified_{modified}, note_{note},
          favorite_{favorite}, active_{active}, fields_{fields} {}

    Card(const QUuid &uuid, const QString &name, long modified, const QString &note, bool favorite, bool active)
        : cardClass_{CardClass::NOTE}, uuid_{uuid}, picture_{Picture::NOTE}, name_{name}, modified_{modified},
          note_{note}, favorite_{favorite}, active_{active}, fields_{{}} {}

    explicit Card(const Card &card);

  public:
    const CardClass             &cardClass() const { return cardClass_; }
    const QUuid                 &uuid() const { return uuid_; }
    const Picture               &picture() const { return picture_; }
    const QString               &name() const { return name_; }
    const QString               &note() const { return note_; }
    bool                         favorite() const { return favorite_; }
    bool                         active() const { return active_; }
    long                         modified() const { return modified_; }
    const std::vector<FieldPtr> &fields() const { return fields_; }

    void setPicture(const Picture &picture) { picture_ = picture; }
    void setName(const QString &name) { name_ = name; }
    void setNote(const QString &note) { note_ = note; }
    void setFavorite(bool favorite) { favorite_ = favorite; }
    void setActive(bool active) { active_ = active; }
    void setFields(const std::vector<FieldPtr> &fields) { fields_ = fields; }

  private:
    const CardClass      &cardClass_;
    QUuid                 uuid_;
    PictureRef            picture_;
    QString               name_;
    long                  modified_;
    QString               note_;
    bool                  favorite_;
    bool                  active_;
    std::vector<FieldPtr> fields_;
};

using CardPtr = std::shared_ptr<Card>;

#endif // CARD_H
