//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "card.hpp"
#include "creditcardtype.hpp"
#include "field.hpp"
#include "localdate.hpp"
#include "serializer.hpp"
#include <gtest/gtest.h>

TEST(PasswordManager, Serializer_serializeAndDeserialize) {
    Serializer::initialize();

    std::vector<Card> cards{
        Card{
            CardClass::CARD,
            UUID::randomUuid(),
            Picture::EMAIL,
            u"Card1",
            0,
            u"Card note 1",
            true,
            true,
            {
                Field{FieldType::EMAIL, u"Field_1_1", u"Value_1_1"},
                Field{FieldType::UNIX_PASSWORD, u"Field_1_2", u"Value_1_2"},
            },
        },
        Card{UUID::randomUuid(), u"Note1", 0, u"Note content", true, true},
        Card{CardClass::CARD,
             UUID::randomUuid(),
             Picture::AIRPLANE,
             u"Card2",
             0,
             u"Card note 2",
             false,
             false,
             {
                 Field{FieldType::EMAIL, u"Field_2_1", u"Value_2_1"},
                 Field{FieldType::UNIX_PASSWORD, u"Field_2_2", u"Value_2_2"},
                 Field{FieldType::HIDDEN, u"Field_2_3", u"Value_2_3"},
                 Field{FieldType::DATE, u"Field_2_4", LocalDate::now()},
                 Field{FieldType::EXPIRATION_MONTH, u"Field_2_5", LocalDate::now()},
                 Field{FieldType::CARD_TYPE, u"Field_2_6", CreditCardType::MIR.ordinal()},
             }},
    };

    std::vector<char> buffer;
    Serializer::serialize(cards, buffer);

    std::vector<Card> deserialized;
    Serializer::deserialize(buffer, deserialized);

    EXPECT_EQ(deserialized, cards);
}
