//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARD_H
#define CARD_H

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

#endif // CARD_H
