/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef PICTURE_H
#define PICTURE_H

#include "enumclass.h"
#include <QIcon>
#include <functional>
#include <string>

class Picture;
using PictureRef = std::reference_wrapper<const Picture>;

class Picture final : public Common::EnumClass<Picture> {
  public:
    static const Picture AIRPLANE;
    static const Picture AMAZON;
    static const Picture AMEX;
    static const Picture APPLE;
    static const Picture AUTO;
    static const Picture BANK;
    static const Picture BITBUCKET;
    static const Picture CD;
    static const Picture CHESS;
    static const Picture CHROME;
    static const Picture CITI;
    static const Picture COMPUTER;
    static const Picture CREDIT_CARD;
    static const Picture DINERS;
    static const Picture EDUCATION;
    static const Picture EMAIL;
    static const Picture FACEBOOK;
    static const Picture FAVORITES;
    static const Picture FEMALE;
    static const Picture FLICKR;
    static const Picture FOLDER;
    static const Picture GENERIC;
    static const Picture GITHUB;
    static const Picture GLASSES;
    static const Picture GPLUS;
    static const Picture HOUSE;
    static const Picture ICQ;
    static const Picture IMPORTANT;
    static const Picture INFO;
    static const Picture INSURANCE;
    static const Picture INTERNET;
    static const Picture IPHONE;
    static const Picture JAVA;
    static const Picture JCB;
    static const Picture LINKEDIN;
    static const Picture MALE;
    static const Picture MASTERCARD;
    static const Picture MEDICINE;
    static const Picture MIR;
    static const Picture MOBILE;
    static const Picture MOZILLA;
    static const Picture NOTE;
    static const Picture NVIDIA;
    static const Picture ODNOKLASSNIKI;
    static const Picture ORIGIN;
    static const Picture PASSPORT;
    static const Picture PAYPAL;
    static const Picture PHONE;
    static const Picture RAIFFEISEN;
    static const Picture REDDIT;
    static const Picture RUSSIA;
    static const Picture SBERBANK;
    static const Picture SHOP;
    static const Picture SKYPE;
    static const Picture STEAM;
    static const Picture TELEGRAM;
    static const Picture TRAIN;
    static const Picture TRASH;
    static const Picture TWITTER;
    static const Picture UNIONPAY;
    static const Picture US;
    static const Picture VISA;
    static const Picture VK;
    static const Picture WALLET;
    static const Picture WIFI;
    static const Picture WOW;
    static const Picture YAHOO;
    static const Picture YANDEX;

  public:
    const QIcon &icon() const;

  private:
    explicit Picture(const std::string &name, const QString &fileName) : EnumClass{name}, fileName_{fileName} {}

  private:
    const QString fileName_;
};

#endif // PICTURE_H
