/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARD_H
#define CARD_H

#include "cardclass.h"
#include "picture.h"
#include <QUuid>

class Field;

class Card final {
  public:
    explicit Card(const CardClass &cardClass, const QUuid &uuid, const Picture &picture, const QString &name,
                  unsigned long modified, const QString &note, bool favorite, bool active,
                  const std::vector<std::shared_ptr<Field>> &fields);
    explicit Card(const QUuid &uuid, const Picture &picture, const QString &name, unsigned long modified,
                  const QString &note, bool favorite, bool active, const std::vector<std::shared_ptr<Field>> &fields);
    explicit Card(const Picture &picture, const QString &name, unsigned long modified,
                  const std::vector<std::shared_ptr<Field>> &fields);
    explicit Card(const QUuid &uuid, const QString &name, unsigned long modified, const QString &note, bool favorite,
                  bool active);
    explicit Card(const QString &name, unsigned long modified);
    explicit Card(const Card &card);
    ~Card();

  public:
    const CardClass &cardClass() const { return cardClass_; }
    const QUuid &uuid() const { return uuid_; }
    const Picture &picture() const { return picture_; }
    const QString &name() const { return name_; }
    const QString &note() const { return note_; }
    bool favorite() const { return favorite_; }
    bool active() const { return active_; }
    unsigned long modified() const { return modified_; }
    const std::vector<std::shared_ptr<Field>> &fields() const { return fields_; }

    void setPicture(const Picture &picture) { picture_ = picture; }
    void setName(const QString &name) { name_ = name; }
    void setNote(const QString &note) { note_ = note; }
    void setActive(bool active) { active_ = active; }
    void setFields(const std::vector<std::shared_ptr<Field>> &fields) { fields_ = fields; }
    void toggleFavorite() noexcept { favorite_ = !favorite_; }
    void toggleActive() noexcept { active_ = !active_; }
    void setModified(unsigned long modified) noexcept { modified_ = modified; }

    bool isCard() const noexcept { return cardClass_ == CardClass::CARD; }
    bool isNote() const noexcept { return cardClass_ == CardClass::NOTE; }

  private:
    const CardClass &cardClass_;
    QUuid uuid_;
    std::reference_wrapper<const Picture> picture_;
    QString name_;
    unsigned long modified_;
    QString note_;
    bool favorite_;
    bool active_;
    std::vector<std::shared_ptr<Field>> fields_;
};

#endif // CARD_H
