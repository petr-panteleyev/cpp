//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "card.hpp"
#include "field.hpp"
#include "serializer.hpp"
#include <gtest/gtest.h>

TEST(PasswordManager, Serializer_serializeAndDeserialize) {
    Serializer::initialize();

    std::vector<Card> cards{
        Card{
            CardClass::CARD,
            QUuid::createUuid(),
            Picture::EMAIL,
            "Card1",
            0,
            "Card note 1",
            true,
            true,
            {
                Field(FieldType::EMAIL, "Field_1_1", "Value_1_1"),
                Field(FieldType::UNIX_PASSWORD, "Field_1_2", "Value_1_2"),
            },
        },
        Card{QUuid::createUuid(), "Note1", 0, "Note content", true, true},
        Card{CardClass::CARD,
             QUuid::createUuid(),
             Picture::AIRPLANE,
             "Card2",
             0,
             "Card note 2",
             false,
             false,
             {
                 Field(FieldType::EMAIL, "Field_2_1", "Value_2_1"),
                 Field(FieldType::UNIX_PASSWORD, "Field_2_2", "Value_2_2"),
                 Field(FieldType::HIDDEN, "Field_2_3", "Value_2_3"),
             }},
    };

    QByteArray buffer;
    Serializer::serialize(cards, buffer);

    std::vector<Card> deserialized;
    Serializer::deserialize(buffer, deserialized);

    EXPECT_EQ(deserialized, cards);
}
