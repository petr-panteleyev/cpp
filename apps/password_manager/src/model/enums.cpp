/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardclass.h"
#include "creditcardtype.h"
#include "fieldtype.h"
#include "picture.h"
#include "recordtype.h"
#include <QApplication>
#include <QDate>
#include <vector>

using std::cref;

// Picture
const Picture Picture::AIRPLANE{"AIRPLANE", "airplane.png"};
const Picture Picture::AMAZON{"AMAZON", "amazon.png"};
const Picture Picture::AMEX{"AMEX", "amex.png"};
const Picture Picture::APPLE{"APPLE", "apple.png"};
const Picture Picture::AUTO{"AUTO", "auto.png"};
const Picture Picture::BANK{"BANK", "bank.png"};
const Picture Picture::BITBUCKET{"BITBUCKET", "bitbucket.png"};
const Picture Picture::CD{"CD", "cd.png"};
const Picture Picture::CHESS{"CHESS", "chess.png"};
const Picture Picture::CHROME{"CHROME", "chrome.png"};
const Picture Picture::CITI{"CITI", "citi.png"};
const Picture Picture::COMPUTER{"COMPUTER", "computer.png"};
const Picture Picture::CREDIT_CARD{"CREDIT_CARD", "credit_card.png"};
const Picture Picture::DINERS{"DINERS", "diners.png"};
const Picture Picture::EDUCATION{"EDUCATION", "education.png"};
const Picture Picture::EMAIL{"EMAIL", "email.png"};
const Picture Picture::FACEBOOK{"FACEBOOK", "facebook.png"};
const Picture Picture::FAVORITES{"FAVORITES", "favorites.png"};
const Picture Picture::FEMALE{"FEMALE", "female.png"};
const Picture Picture::FLICKR{"FLICKR", "flickr.png"};
const Picture Picture::FOLDER{"FOLDER", "folder.png"};
const Picture Picture::GENERIC{"GENERIC", "generic.png"};
const Picture Picture::GITHUB{"GITHUB", "github.png"};
const Picture Picture::GLASSES{"GLASSES", "glasses.png"};
const Picture Picture::GPLUS{"GPLUS", "gplus.png"};
const Picture Picture::HOUSE{"HOUSE", "house.png"};
const Picture Picture::ICQ{"ICQ", "icq.png"};
const Picture Picture::IMPORTANT{"IMPORTANT", "important.png"};
const Picture Picture::INFO{"INFO", "info.png"};
const Picture Picture::INSURANCE{"INSURANCE", "insurance.png"};
const Picture Picture::INTERNET{"INTERNET", "internet.png"};
const Picture Picture::IPHONE{"IPHONE", "iphone.png"};
const Picture Picture::JAVA{"JAVA", "java.png"};
const Picture Picture::JCB{"JCB", "jcb.png"};
const Picture Picture::LINKEDIN{"LINKEDIN", "linkedin.png"};
const Picture Picture::MALE{"MALE", "male.png"};
const Picture Picture::MASTERCARD{"MASTERCARD", "mastercard.png"};
const Picture Picture::MEDICINE{"MEDICINE", "medicine.png"};
const Picture Picture::MIR{"MIR", "mir.png"};
const Picture Picture::MOBILE{"MOBILE", "mobile.png"};
const Picture Picture::MOZILLA{"MOZILLA", "mozilla.png"};
const Picture Picture::NOTE{"NOTE", "note.png"};
const Picture Picture::NVIDIA{"NVIDIA", "nvidia.png"};
const Picture Picture::ODNOKLASSNIKI{"ODNOKLASSNIKI", "odnoklassniki.png"};
const Picture Picture::ORIGIN{"ORIGIN", "origin.png"};
const Picture Picture::PASSPORT{"PASSPORT", "passport.png"};
const Picture Picture::PAYPAL{"PAYPAL", "paypal.png"};
const Picture Picture::PHONE{"PHONE", "phone.png"};
const Picture Picture::RAIFFEISEN{"RAIFFEISEN", "raiffeisen.png"};
const Picture Picture::REDDIT{"REDDIT", "reddit.png"};
const Picture Picture::RUSSIA{"RUSSIA", "russia.png"};
const Picture Picture::SBERBANK{"SBERBANK", "sberbank.png"};
const Picture Picture::SHOP{"SHOP", "shop.png"};
const Picture Picture::SKYPE{"SKYPE", "skype.png"};
const Picture Picture::STEAM{"STEAM", "steam.png"};
const Picture Picture::TELEGRAM{"TELEGRAM", "telegram.png"};
const Picture Picture::TRAIN{"TRAIN", "train.png"};
const Picture Picture::TRASH{"TRASH", "trash.png"};
const Picture Picture::TWITTER{"TWITTER", "twitter.png"};
const Picture Picture::UNIONPAY{"UNIONPAY", "unionpay.png"};
const Picture Picture::US{"US", "us.png"};
const Picture Picture::VISA{"VISA", "visa.png"};
const Picture Picture::VK{"VK", "vk.png"};
const Picture Picture::WALLET{"WALLET", "wallet.png"};
const Picture Picture::WIFI{"WIFI", "wifi.png"};
const Picture Picture::WOW{"WOW", "wow.png"};
const Picture Picture::YAHOO{"YAHOO", "yahoo.png"};
const Picture Picture::YANDEX{"YANDEX", "yandex.png"};

template <>
const std::vector<PictureRef> Common::EnumClass<Picture>::values_{
    cref(Picture::AIRPLANE),    cref(Picture::AMAZON),    cref(Picture::AMEX),      cref(Picture::APPLE),
    cref(Picture::AUTO),        cref(Picture::BANK),      cref(Picture::BITBUCKET), cref(Picture::CD),
    cref(Picture::CHESS),       cref(Picture::CHROME),    cref(Picture::CITI),      cref(Picture::COMPUTER),
    cref(Picture::CREDIT_CARD), cref(Picture::DINERS),    cref(Picture::EDUCATION), cref(Picture::EMAIL),
    cref(Picture::FACEBOOK),    cref(Picture::FAVORITES), cref(Picture::FEMALE),    cref(Picture::FLICKR),
    cref(Picture::FOLDER),      cref(Picture::GENERIC),   cref(Picture::GITHUB),    cref(Picture::GLASSES),
    cref(Picture::GPLUS),       cref(Picture::HOUSE),     cref(Picture::ICQ),       cref(Picture::IMPORTANT),
    cref(Picture::INFO),        cref(Picture::INSURANCE), cref(Picture::INTERNET),  cref(Picture::IPHONE),
    cref(Picture::JAVA),        cref(Picture::JCB),       cref(Picture::LINKEDIN),  cref(Picture::MALE),
    cref(Picture::MASTERCARD),  cref(Picture::MEDICINE),  cref(Picture::MIR),       cref(Picture::MOBILE),
    cref(Picture::MOZILLA),     cref(Picture::NOTE),      cref(Picture::NVIDIA),    cref(Picture::ODNOKLASSNIKI),
    cref(Picture::ORIGIN),      cref(Picture::PASSPORT),  cref(Picture::PAYPAL),    cref(Picture::PHONE),
    cref(Picture::RAIFFEISEN),  cref(Picture::REDDIT),    cref(Picture::RUSSIA),    cref(Picture::SBERBANK),
    cref(Picture::SHOP),        cref(Picture::SKYPE),     cref(Picture::STEAM),     cref(Picture::TELEGRAM),
    cref(Picture::TRAIN),       cref(Picture::TRASH),     cref(Picture::TWITTER),   cref(Picture::UNIONPAY),
    cref(Picture::US),          cref(Picture::VISA),      cref(Picture::VK),        cref(Picture::WALLET),
    cref(Picture::WIFI),        cref(Picture::WOW),       cref(Picture::YAHOO),     cref(Picture::YANDEX),
};

// CardClass
const CardClass CardClass::CARD{"CARD"};
const CardClass CardClass::NOTE{"NOTE"};

template <>
const std::vector<CardClassRef> Common::EnumClass<CardClass>::values_{
    cref(CardClass::CARD),
    cref(CardClass::NOTE),
};

// FieldType
const FieldType FieldType::STRING{"STRING"};
const FieldType FieldType::HIDDEN{"HIDDEN", true};
const FieldType FieldType::EMAIL{"EMAIL"};
const FieldType FieldType::CREDIT_CARD_NUMBER{"CREDIT_CARD_NUMBER"};
const FieldType FieldType::LINK{"LINK"};
const FieldType FieldType::PIN{"PIN", true};
const FieldType FieldType::UNIX_PASSWORD{"UNIX_PASSWORD", true};
const FieldType FieldType::SHORT_PASSWORD{"SHORT_PASSWORD", true};
const FieldType FieldType::LONG_PASSWORD{"LONG_PASSWORD", true};
const FieldType FieldType::CARD_TYPE{"CARD_TYPE"};
const FieldType FieldType::DATE{"DATE"};
const FieldType FieldType::EXPIRATION_MONTH{"EXPIRATION_MONTH"};

template <>
const std::vector<FieldTypeRef> Common::EnumClass<FieldType>::values_{
    cref(FieldType::STRING),        cref(FieldType::HIDDEN),
    cref(FieldType::EMAIL),         cref(FieldType::CREDIT_CARD_NUMBER),
    cref(FieldType::LINK),          cref(FieldType::PIN),
    cref(FieldType::UNIX_PASSWORD), cref(FieldType::SHORT_PASSWORD),
    cref(FieldType::LONG_PASSWORD), cref(FieldType::CARD_TYPE),
    cref(FieldType::DATE),          cref(FieldType::EXPIRATION_MONTH),
};

// CreditCardType
const CreditCardType CreditCardType::AMEX("AMEX", "American Express", Picture::AMEX);
const CreditCardType CreditCardType::DINERS("DINERS", "Diners Club", Picture::DINERS);
const CreditCardType CreditCardType::JCB("JCB", "JCB", Picture::JCB);
const CreditCardType CreditCardType::MASTERCARD("MASTERCARD", "MasterCard", Picture::MASTERCARD);
const CreditCardType CreditCardType::MIR("MIR", "Мир", Picture::MIR);
const CreditCardType CreditCardType::PAYPAL("PAYPAL", "PayPal", Picture::PAYPAL);
const CreditCardType CreditCardType::UNION_PAY("UNION_PAY", "Union Pay", Picture::UNIONPAY);
const CreditCardType CreditCardType::VISA("VISA", "VISA", Picture::VISA);
const CreditCardType CreditCardType::OTHER("OTHER", "Other", Picture::CREDIT_CARD);

template <>
const std::vector<CreditCardTypeRef> Common::EnumClass<CreditCardType>::values_{
    cref(CreditCardType::AMEX),       cref(CreditCardType::DINERS), cref(CreditCardType::JCB),
    cref(CreditCardType::MASTERCARD), cref(CreditCardType::MIR),    cref(CreditCardType::PAYPAL),
    cref(CreditCardType::UNION_PAY),  cref(CreditCardType::VISA),   cref(CreditCardType::OTHER),
};

// RecordType
const RecordType RecordType::EMPTY("EMPTY", Picture::GENERIC, {});
const RecordType RecordType::CREDIT_CARD(
    "CREDIT_CARD", Picture::CREDIT_CARD,
    {
        std::make_shared<Field>(FieldType::STRING, QApplication::translate("RecordType", "Card Provider"), ""),
        std::make_shared<Field>(FieldType::CARD_TYPE, QApplication::translate("RecordType", "Card Type"),
                                CreditCardType::MIR.ordinal()),
        std::make_shared<Field>(FieldType::CREDIT_CARD_NUMBER, QApplication::translate("RecordType", "Card Number"),
                                ""),
        std::make_shared<Field>(FieldType::EXPIRATION_MONTH, QApplication::translate("RecordType", "Expiration Date"),
                                QDate::currentDate()),
        std::make_shared<Field>(FieldType::PIN, "PIN", ""),
        std::make_shared<Field>(FieldType::STRING, QApplication::translate("RecordType", "Name on Card"), ""),
        std::make_shared<Field>(FieldType::STRING, QApplication::translate("RecordType", "Phone Number"), ""),
        std::make_shared<Field>(FieldType::HIDDEN, "CVC#", ""),
        std::make_shared<Field>(FieldType::STRING, QApplication::translate("RecordType", "Login"), ""),
        std::make_shared<Field>(FieldType::LONG_PASSWORD, QApplication::translate("RecordType", "Password"), ""),
    });
const RecordType RecordType::PASSWORD(
    "PASSWORD", Picture::GENERIC,
    {
        std::make_shared<Field>(FieldType::STRING, QApplication::translate("RecordType", "System"), ""),
        std::make_shared<Field>(FieldType::STRING, QApplication::translate("RecordType", "Login"), ""),
        std::make_shared<Field>(FieldType::LONG_PASSWORD, QApplication::translate("RecordType", "Password"), ""),
        std::make_shared<Field>(FieldType::LINK, "URL", ""),
    });

template <>
const std::vector<RecordTypeRef> Common::EnumClass<RecordType>::values_{
    cref(RecordType::EMPTY),
    cref(RecordType::CREDIT_CARD),
    cref(RecordType::PASSWORD),
};
