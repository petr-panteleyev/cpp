//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "cardclass.h"
#include "field.h"
#include "picture.h"
#include <QUuid>
#include <vector>

class Card final {
  public:
    explicit Card(const CardClass &cardClass, const QUuid &uuid, const Picture &picture, const QString &name,
                  unsigned long modified, const QString &note, bool favorite, bool active,
                  const std::vector<Field> &fields);

    explicit Card(const QUuid &uuid, const Picture &picture, const QString &name, unsigned long modified,
                  const QString &note, bool favorite, bool active, const std::vector<Field> &fields);

    explicit Card(const Picture &picture, const QString &name, unsigned long modified,
                  const std::vector<Field> &fields);

    explicit Card(const QUuid &uuid, const QString &name, unsigned long modified, const QString &note, bool favorite,
                  bool active);

    explicit Card(const QString &name, unsigned long modified);

    explicit Card();

    Card(const Card &card) = default;
    ~Card() = default;

    Card &operator=(const Card &) = default;

    bool operator==(const Card &that) const noexcept {
        return this->cardClass_.get() == that.cardClass_.get() && this->uuid_ == that.uuid_ &&
               this->picture_.get() == that.picture_.get() && this->name_ == that.name_ &&
               this->modified_ == that.modified_ && this->note_ == that.note_ && this->favorite_ == that.favorite_ &&
               this->active_ == that.active_ && this->fields_ == that.fields_;
    }

  public:
    const CardClass &cardClass() const { return cardClass_; }
    const QUuid &uuid() const { return uuid_; }
    const Picture &picture() const { return picture_; }
    const QString &name() const { return name_; }
    const QString &note() const { return note_; }
    bool favorite() const { return favorite_; }
    bool active() const { return active_; }
    unsigned long modified() const { return modified_; }

    const std::vector<Field> &fields() const { return fields_; }
    void setActive(bool active) noexcept { active_ = active; }
    void toggleActive(bool active) noexcept { active_ = !active_; }
    void setFavorite(bool favorite) noexcept { favorite_ = favorite; }
    void toggleFavorite() noexcept { favorite_ = !favorite_; }

    bool isCard() const noexcept { return cardClass_ == CardClass::CARD; }
    bool isNote() const noexcept { return cardClass_ == CardClass::NOTE; }

  private:
    CardClassRef cardClass_;
    QUuid uuid_;
    PictureRef picture_;
    QString name_;
    unsigned long modified_;
    QString note_;
    bool favorite_;
    bool active_;
    std::vector<Field> fields_;
};
