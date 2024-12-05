/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARDCLASS_H
#define CARDCLASS_H

#include <string>

class CardClass;

enum class CardClassEnum : unsigned { CARD = 0, NOTE };

class CardClass {
  public:
    static const CardClass CARD;
    static const CardClass NOTE;

  public:
    static const CardClass &valueOf(const std::string &name);
    static const CardClass &valueOf(CardClassEnum value);

    const std::string &name() const { return name_; }
    CardClassEnum      ordinal() const { return ordinal_; }

    friend bool operator==(const CardClass &x, const CardClass &y) { return x.ordinal_ == y.ordinal_; }

  private:
    CardClass(CardClassEnum ordinal, const std::string &name) : ordinal_{ordinal}, name_{name} {}
    CardClass(const CardClass &) = delete;
    CardClass(const CardClass &&) = delete;

  private:
    const CardClassEnum ordinal_;
    const std::string   name_;
};

inline const CardClass CardClass::CARD{CardClassEnum::CARD, "CARD"};
inline const CardClass CardClass::NOTE{CardClassEnum::NOTE, "NOTE"};

#endif // CARDCLASS_H
