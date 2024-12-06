/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef PICTURE_H
#define PICTURE_H

#include <QIcon>
#include <functional>
#include <string>

class Picture;
using PictureRef = std::reference_wrapper<const Picture>;

class Picture final {
  public:
    static const Picture AMEX;
    static const Picture CREDIT_CARD;
    static const Picture DINERS;
    static const Picture FAVORITES;
    static const Picture GENERIC;
    static const Picture JCB;
    static const Picture MASTERCARD;
    static const Picture MIR;
    static const Picture MOBILE;
    static const Picture NOTE;
    static const Picture PAYPAL;
    static const Picture TRASH;
    static const Picture UNIONPAY;
    static const Picture VISA;

  public:
    static const Picture &valueOf(const std::string &name);

  public:
    const std::string &name() const { return name_; }
    const QIcon       &icon() const;

    friend bool operator==(const Picture &x, const Picture &y) { return x.ordinal_ == y.ordinal_; }

  private:
    Picture(unsigned ordinal, const std::string &name, const QString &fileName)
        : ordinal_{ordinal}, name_{name}, fileName_{fileName} {}
    Picture(const Picture &) = delete;
    Picture(const Picture &&) = delete;

  private:
    const unsigned    ordinal_;
    const std::string name_;
    const QString     fileName_;

    static const std::vector<PictureRef> values_;
};

#endif // PICTURE_H
