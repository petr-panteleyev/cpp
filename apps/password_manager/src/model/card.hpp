//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "cardclass.hpp"
#include "field.hpp"
#include "picture.hpp"
#include "uuid.hpp"
#include <vector>

class Card final {
  public:
    explicit Card(const CardClass &cardClass, const UUID::UUID &uuid, const Picture &picture,
                  const std::u16string &name, unsigned long modified, const std::u16string &note, bool favorite,
                  bool active, const std::vector<Field> &fields);

    explicit Card(const UUID::UUID &uuid, const Picture &picture, const std::u16string &name, unsigned long modified,
                  const std::u16string &note, bool favorite, bool active, const std::vector<Field> &fields);

    explicit Card(const Picture &picture, const std::u16string &name, unsigned long modified,
                  const std::vector<Field> &fields);

    explicit Card(const UUID::UUID &uuid, const std::u16string &name, unsigned long modified,
                  const std::u16string &note, bool favorite, bool active);

    explicit Card(const std::u16string &name, unsigned long modified);

    explicit Card();

    Card(const Card &card) = default;
    Card(Card &&) = default;
    ~Card() = default;

    Card &operator=(const Card &) = default;

    bool operator==(const Card &that) const noexcept;

  public:
    const CardClass &cardClass() const { return cardClass_; }
    const UUID::UUID &uuid() const { return uuid_; }
    const Picture &picture() const { return picture_; }
    const std::u16string &name() const { return name_; }
    const std::u16string &note() const { return note_; }
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
    UUID::UUID uuid_;
    PictureRef picture_;
    std::u16string name_;
    unsigned long modified_;
    std::u16string note_;
    bool favorite_;
    bool active_;
    std::vector<Field> fields_;
};
