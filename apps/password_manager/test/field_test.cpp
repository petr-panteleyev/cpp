//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "creditcardtype.h"
#include "field.h"
#include <QDate>
#include <gtest/gtest.h>

namespace {
struct FieldDeserializeTestParams {
    QString stringValue_;
    FieldTypeRef type_;
    QVariant expected_;
};

class FieldTest : public ::testing::TestWithParam<FieldDeserializeTestParams> {};

} // namespace

TEST_P(FieldTest, Field_deserialize) {
    auto [stringValue, type, expected] = GetParam();

    auto actual = Field::deserialize(stringValue, type);
    EXPECT_EQ(actual, expected);
}

INSTANTIATE_TEST_SUITE_P(
    PasswordManager, FieldTest,
    ::testing::Values(
        FieldDeserializeTestParams{"String", FieldType::STRING, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::HIDDEN, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::EMAIL, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::CREDIT_CARD_NUMBER, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::LINK, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::PIN, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::UNIX_PASSWORD, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::SHORT_PASSWORD, QVariant("String")},
        FieldDeserializeTestParams{"String", FieldType::LONG_PASSWORD, QVariant("String")},
        FieldDeserializeTestParams{"MASTERCARD", FieldType::CARD_TYPE, QVariant(CreditCardType::MASTERCARD.ordinal())},
        FieldDeserializeTestParams{"2025-10-11", FieldType::DATE, QVariant(QDate(2025, 10, 11))},
        FieldDeserializeTestParams{"2025-01-05", FieldType::EXPIRATION_MONTH, QVariant(QDate(2025, 1, 5))}),
    [](const ::testing::TestParamInfo<FieldTest::ParamType> &params) { return params.param.type_.get().name(); });
