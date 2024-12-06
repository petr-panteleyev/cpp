/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardclass.h"
#include "creditcardtype.h"
#include "fieldtype.h"
#include "picture.h"
#include <vector>

// Picture
static unsigned pictureOrdinal = 0;

const Picture Picture::AMEX{pictureOrdinal++, "AMEX", "amex.png"};
const Picture Picture::CREDIT_CARD{pictureOrdinal++, "CREDIT_CARD", "credit_card.png"};
const Picture Picture::DINERS{pictureOrdinal++, "DINERS", "diners.png"};
const Picture Picture::FAVORITES{pictureOrdinal++, "FAVORITES", "favorites.png"};
const Picture Picture::GENERIC{pictureOrdinal++, "GENERIC", "generic.png"};
const Picture Picture::JCB{pictureOrdinal++, "JCB", "jcb.png"};
const Picture Picture::MASTERCARD{pictureOrdinal++, "MASTERCARD", "mastercard.png"};
const Picture Picture::MIR{pictureOrdinal++, "MIR", "mir.png"};
const Picture Picture::MOBILE{pictureOrdinal++, "MOBILE", "mobile.png"};
const Picture Picture::NOTE{pictureOrdinal++, "NOTE", "note.png"};
const Picture Picture::PAYPAL{pictureOrdinal++, "PAYPAL", "paypal.png"};
const Picture Picture::TRASH{pictureOrdinal++, "TRASH", "trash.png"};
const Picture Picture::UNIONPAY{pictureOrdinal++, "UNIONPAY", "unionpay.png"};
const Picture Picture::VISA{pictureOrdinal++, "VISA", "visa.png"};

const std::vector<PictureRef> Picture::values_{
    std::cref(Picture::AMEX),       std::cref(Picture::CREDIT_CARD), std::cref(Picture::DINERS),
    std::cref(Picture::FAVORITES),  std::cref(Picture::GENERIC),     std::cref(Picture::JCB),
    std::cref(Picture::MASTERCARD), std::cref(Picture::MIR),         std::cref(Picture::MOBILE),
    std::cref(Picture::NOTE),       std::cref(Picture::PAYPAL),      std::cref(Picture::TRASH),
    std::cref(Picture::UNIONPAY),   std::cref(Picture::VISA),
};

// CardClass
static unsigned cardClassOrdinal = 0;

const CardClass CardClass::CARD{cardClassOrdinal++, "CARD"};
const CardClass CardClass::NOTE{cardClassOrdinal++, "NOTE"};

const std::vector<CardClassRef> CardClass::values_{
    std::cref(CardClass::CARD),
    std::cref(CardClass::NOTE),
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
    std::cref(FieldType::STRING),        std::cref(FieldType::HIDDEN),
    std::cref(FieldType::EMAIL),         std::cref(FieldType::CREDIT_CARD_NUMBER),
    std::cref(FieldType::LINK),          std::cref(FieldType::PIN),
    std::cref(FieldType::UNIX_PASSWORD), std::cref(FieldType::SHORT_PASSWORD),
    std::cref(FieldType::LONG_PASSWORD), std::cref(FieldType::CARD_TYPE),
    std::cref(FieldType::DATE),          std::cref(FieldType::EXPIRATION_MONTH),
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
    std::cref(CreditCardType::AMEX),       std::cref(CreditCardType::DINERS), std::cref(CreditCardType::JCB),
    std::cref(CreditCardType::MASTERCARD), std::cref(CreditCardType::MIR),    std::cref(CreditCardType::PAYPAL),
    std::cref(CreditCardType::UNION_PAY),  std::cref(CreditCardType::VISA),   std::cref(CreditCardType::OTHER),
};
