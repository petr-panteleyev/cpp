/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardclass.h"
#include "creditcardtype.h"
#include "fieldtype.h"
#include "picture.h"
#include <vector>

using std::cref;

// Picture
static unsigned pictureOrdinal = 0;

const Picture Picture::AIRPLANE{pictureOrdinal++, "AIRPLANE", "airplane.png"};
const Picture Picture::AMAZON{pictureOrdinal++, "AMAZON", "amazon.png"};
const Picture Picture::AMEX{pictureOrdinal++, "AMEX", "amex.png"};
const Picture Picture::APPLE{pictureOrdinal++, "APPLE", "apple.png"};
const Picture Picture::AUTO{pictureOrdinal++, "AUTO", "auto.png"};
const Picture Picture::BANK{pictureOrdinal++, "BANK", "bank.png"};
const Picture Picture::BITBUCKET{pictureOrdinal++, "BITBUCKET", "bitbucket.png"};
const Picture Picture::CD{pictureOrdinal++, "CD", "cd.png"};
const Picture Picture::CHESS{pictureOrdinal++, "CHESS", "chess.png"};
const Picture Picture::CHROME{pictureOrdinal++, "CHROME", "chrome.png"};
const Picture Picture::CITI{pictureOrdinal++, "CITI", "citi.png"};
const Picture Picture::COMPUTER{pictureOrdinal++, "COMPUTER", "computer.png"};
const Picture Picture::CREDIT_CARD{pictureOrdinal++, "CREDIT_CARD", "credit_card.png"};
const Picture Picture::DINERS{pictureOrdinal++, "DINERS", "diners.png"};
const Picture Picture::EDUCATION{pictureOrdinal++, "EDUCATION", "education.png"};
const Picture Picture::EMAIL{pictureOrdinal++, "EMAIL", "email.png"};
const Picture Picture::FACEBOOK{pictureOrdinal++, "FACEBOOK", "facebook.png"};
const Picture Picture::FAVORITES{pictureOrdinal++, "FAVORITES", "favorites.png"};
const Picture Picture::FEMALE{pictureOrdinal++, "FEMALE", "female.png"};
const Picture Picture::FLICKR{pictureOrdinal++, "FLICKR", "flickr.png"};
const Picture Picture::FOLDER{pictureOrdinal++, "FOLDER", "folder.png"};
const Picture Picture::GENERIC{pictureOrdinal++, "GENERIC", "generic.png"};
const Picture Picture::GITHUB{pictureOrdinal++, "GITHUB", "github.png"};
const Picture Picture::GLASSES{pictureOrdinal++, "GLASSES", "glasses.png"};
const Picture Picture::GPLUS{pictureOrdinal++, "GPLUS", "gplus.png"};
const Picture Picture::HOUSE{pictureOrdinal++, "HOUSE", "house.png"};
const Picture Picture::ICQ{pictureOrdinal++, "ICQ", "icq.png"};
const Picture Picture::IMPORTANT{pictureOrdinal++, "IMPORTANT", "important.png"};
const Picture Picture::INFO{pictureOrdinal++, "INFO", "info.png"};
const Picture Picture::INSURANCE{pictureOrdinal++, "INSURANCE", "insurance.png"};
const Picture Picture::INTERNET{pictureOrdinal++, "INTERNET", "internet.png"};
const Picture Picture::IPHONE{pictureOrdinal++, "IPHONE", "iphone.png"};
const Picture Picture::JAVA{pictureOrdinal++, "JAVA", "java.png"};
const Picture Picture::JCB{pictureOrdinal++, "JCB", "jcb.png"};
const Picture Picture::LINKEDIN{pictureOrdinal++, "LINKEDIN", "linkedin.png"};
const Picture Picture::MALE{pictureOrdinal++, "MALE", "male.png"};
const Picture Picture::MASTERCARD{pictureOrdinal++, "MASTERCARD", "mastercard.png"};
const Picture Picture::MEDICINE{pictureOrdinal++, "MEDICINE", "medicine.png"};
const Picture Picture::MIR{pictureOrdinal++, "MIR", "mir.png"};
const Picture Picture::MOBILE{pictureOrdinal++, "MOBILE", "mobile.png"};
const Picture Picture::MOZILLA{pictureOrdinal++, "MOZILLA", "mozilla.png"};
const Picture Picture::NOTE{pictureOrdinal++, "NOTE", "note.png"};
const Picture Picture::NVIDIA{pictureOrdinal++, "NVIDIA", "nvidia.png"};
const Picture Picture::ODNOKLASSNIKI{pictureOrdinal++, "ODNOKLASSNIKI", "odnoklassniki.png"};
const Picture Picture::ORIGIN{pictureOrdinal++, "ORIGIN", "origin.png"};
const Picture Picture::PASSPORT{pictureOrdinal++, "PASSPORT", "passport.png"};
const Picture Picture::PAYPAL{pictureOrdinal++, "PAYPAL", "paypal.png"};
const Picture Picture::PHONE{pictureOrdinal++, "PHONE", "phone.png"};
const Picture Picture::RAIFFEISEN{pictureOrdinal++, "RAIFFEISEN", "raiffeisen.png"};
const Picture Picture::REDDIT{pictureOrdinal++, "REDDIT", "reddit.png"};
const Picture Picture::RUSSIA{pictureOrdinal++, "RUSSIA", "russia.png"};
const Picture Picture::SBERBANK{pictureOrdinal++, "SBERBANK", "sberbank.png"};
const Picture Picture::SHOP{pictureOrdinal++, "SHOP", "shop.png"};
const Picture Picture::SKYPE{pictureOrdinal++, "SKYPE", "skype.png"};
const Picture Picture::STEAM{pictureOrdinal++, "STEAM", "steam.png"};
const Picture Picture::TELEGRAM{pictureOrdinal++, "TELEGRAM", "telegram.png"};
const Picture Picture::TRAIN{pictureOrdinal++, "TRAIN", "train.png"};
const Picture Picture::TRASH{pictureOrdinal++, "TRASH", "trash.png"};
const Picture Picture::TWITTER{pictureOrdinal++, "TWITTER", "twitter.png"};
const Picture Picture::UNIONPAY{pictureOrdinal++, "UNIONPAY", "unionpay.png"};
const Picture Picture::US{pictureOrdinal++, "US", "us.png"};
const Picture Picture::VISA{pictureOrdinal++, "VISA", "visa.png"};
const Picture Picture::VK{pictureOrdinal++, "VK", "vk.png"};
const Picture Picture::WALLET{pictureOrdinal++, "WALLET", "wallet.png"};
const Picture Picture::WIFI{pictureOrdinal++, "WIFI", "wifi.png"};
const Picture Picture::WOW{pictureOrdinal++, "WOW", "wow.png"};
const Picture Picture::YAHOO{pictureOrdinal++, "YAHOO", "yahoo.png"};
const Picture Picture::YANDEX{pictureOrdinal++, "YANDEX", "yandex.png"};

const std::vector<PictureRef> Picture::values_{
    cref(AIRPLANE), cref(AMAZON),     cref(AMEX),        cref(APPLE),         cref(AUTO),
    cref(BANK),     cref(BITBUCKET),  cref(CD),          cref(CHESS),         cref(CHROME),
    cref(CITI),     cref(COMPUTER),   cref(CREDIT_CARD), cref(DINERS),        cref(EDUCATION),
    cref(EMAIL),    cref(FACEBOOK),   cref(FAVORITES),   cref(FEMALE),        cref(FLICKR),
    cref(FOLDER),   cref(GENERIC),    cref(GITHUB),      cref(GLASSES),       cref(GPLUS),
    cref(HOUSE),    cref(ICQ),        cref(IMPORTANT),   cref(INFO),          cref(INSURANCE),
    cref(INTERNET), cref(IPHONE),     cref(JAVA),        cref(JCB),           cref(LINKEDIN),
    cref(MALE),     cref(MASTERCARD), cref(MEDICINE),    cref(MIR),           cref(MOBILE),
    cref(MOZILLA),  cref(NOTE),       cref(NVIDIA),      cref(ODNOKLASSNIKI), cref(ORIGIN),
    cref(PASSPORT), cref(PAYPAL),     cref(PHONE),       cref(RAIFFEISEN),    cref(REDDIT),
    cref(RUSSIA),   cref(SBERBANK),   cref(SHOP),        cref(SKYPE),         cref(STEAM),
    cref(TELEGRAM), cref(TRAIN),      cref(TRASH),       cref(TWITTER),       cref(UNIONPAY),
    cref(US),       cref(VISA),       cref(VK),          cref(WALLET),        cref(WIFI),
    cref(WOW),      cref(YAHOO),      cref(YANDEX),
};

// CardClass
static unsigned cardClassOrdinal = 0;

const CardClass CardClass::CARD{cardClassOrdinal++, "CARD"};
const CardClass CardClass::NOTE{cardClassOrdinal++, "NOTE"};

const std::vector<CardClassRef> CardClass::values_{
    cref(CARD),
    cref(NOTE),
};

// FieldType
static unsigned fieldTypeOrdinal = 0;

const FieldType FieldType::STRING{fieldTypeOrdinal++, "STRING"};
const FieldType FieldType::HIDDEN{fieldTypeOrdinal++, "HIDDEN", true};
const FieldType FieldType::EMAIL{fieldTypeOrdinal++, "EMAIL"};
const FieldType FieldType::CREDIT_CARD_NUMBER{fieldTypeOrdinal++, "CREDIT_CARD_NUMBER"};
const FieldType FieldType::LINK{fieldTypeOrdinal++, "LINK"};
const FieldType FieldType::PIN{fieldTypeOrdinal++, "PIN", true};
const FieldType FieldType::UNIX_PASSWORD{fieldTypeOrdinal++, "UNIX_PASSWORD", true};
const FieldType FieldType::SHORT_PASSWORD{fieldTypeOrdinal++, "SHORT_PASSWORD", true};
const FieldType FieldType::LONG_PASSWORD{fieldTypeOrdinal++, "LONG_PASSWORD", true};
const FieldType FieldType::CARD_TYPE{fieldTypeOrdinal++, "CARD_TYPE"};
const FieldType FieldType::DATE{fieldTypeOrdinal++, "DATE"};
const FieldType FieldType::EXPIRATION_MONTH{fieldTypeOrdinal++, "EXPIRATION_MONTH"};

const std::vector<FieldTypeRef> FieldType::values_{
    cref(STRING),        cref(HIDDEN),    cref(EMAIL),         cref(CREDIT_CARD_NUMBER),
    cref(LINK),          cref(PIN),       cref(UNIX_PASSWORD), cref(SHORT_PASSWORD),
    cref(LONG_PASSWORD), cref(CARD_TYPE), cref(DATE),          cref(EXPIRATION_MONTH),
};

// CreditCardType
static unsigned creditCardTypeOrdinal = 0;

const CreditCardType CreditCardType::AMEX(creditCardTypeOrdinal++, "AMEX", "American Express", Picture::AMEX);
const CreditCardType CreditCardType::DINERS(creditCardTypeOrdinal++, "DINERS", "Diners Club", Picture::DINERS);
const CreditCardType CreditCardType::JCB(creditCardTypeOrdinal++, "JCB", "JCB", Picture::JCB);
const CreditCardType CreditCardType::MASTERCARD(creditCardTypeOrdinal++, "MASTERCARD", "MasterCard",
                                                Picture::MASTERCARD);
const CreditCardType CreditCardType::MIR(creditCardTypeOrdinal++, "MIR", "Мир", Picture::MIR);
const CreditCardType CreditCardType::PAYPAL(creditCardTypeOrdinal++, "PAYPAL", "PayPal", Picture::PAYPAL);
const CreditCardType CreditCardType::UNION_PAY(creditCardTypeOrdinal++, "UNION_PAY", "Union Pay", Picture::UNIONPAY);
const CreditCardType CreditCardType::VISA(creditCardTypeOrdinal++, "VISA", "VISA", Picture::VISA);
const CreditCardType CreditCardType::OTHER(creditCardTypeOrdinal++, "OTHER", "Other", Picture::CREDIT_CARD);

const std::vector<CreditCardTypeRef> CreditCardType::values_{
    cref(AMEX),   cref(DINERS),    cref(JCB),  cref(MASTERCARD), cref(MIR),
    cref(PAYPAL), cref(UNION_PAY), cref(VISA), cref(OTHER),
};
