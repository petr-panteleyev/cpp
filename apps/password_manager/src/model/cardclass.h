/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARDCLASS_H
#define CARDCLASS_H

#include <functional>
#include <string>
#include <vector>

class CardClass;
using CardClassRef = std::reference_wrapper<const CardClass>;

class CardClass {
  public:
    static const CardClass CARD;
    static const CardClass NOTE;

  public:
    static const CardClass &valueOf(const std::string &name);

    const std::string &name() const { return name_; }

    friend bool operator==(const CardClass &x, const CardClass &y) { return x.ordinal_ == y.ordinal_; }

  private:
    CardClass(unsigned ordinal, const std::string &name) : ordinal_{ordinal}, name_{name} {}
    CardClass(const CardClass &) = delete;
    CardClass(const CardClass &&) = delete;

  private:
    const unsigned    ordinal_;
    const std::string name_;

    static const std::vector<CardClassRef> values_;
};

#endif // CARDCLASS_H
