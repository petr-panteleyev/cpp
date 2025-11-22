//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "creditcardtype.hpp"
#include "field.hpp"
#include "ui_tools.hpp"
#include <gtest/gtest.h>

namespace {

struct FieldStringParams {
    Field field_;
    QString string_;
};

class FieldStringTest : public ::testing::TestWithParam<FieldStringParams> {};

struct FieldConvertValueTestParams {
    Field field_;
    FieldTypeRef newType_;
    Field::FieldValue newValue_;
};

class FieldConvertValueTest : public ::testing::TestWithParam<FieldConvertValueTestParams> {};

constexpr std::chrono::year_month_day DATE_VALUE{std::chrono::year{2025}, std::chrono::month{11}, std::chrono::day{1}};
const std::u16string STRING_VALUE{u"String value"};
const std::u16string FIELD_NAME{u"Field Name"};

} // namespace

INSTANTIATE_TEST_SUITE_P(
    UiTools, FieldStringTest,
    ::testing::Values(FieldStringParams{Field{FieldType::STRING, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::HIDDEN, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::EMAIL, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::CREDIT_CARD_NUMBER, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::LINK, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::PIN, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::UNIX_PASSWORD, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::SHORT_PASSWORD, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::LONG_PASSWORD, u"name", STRING_VALUE}, "String value"},
                      FieldStringParams{Field{FieldType::DATE, u"name", DATE_VALUE}, "01.11.2025"},
                      FieldStringParams{Field{FieldType::EXPIRATION_MONTH, u"name", DATE_VALUE}, "11/25"},
                      FieldStringParams{Field{FieldType::CARD_TYPE, u"name", CreditCardType::MASTERCARD.ordinal()},
                                        "MasterCard"}),
    [](const testing::TestParamInfo<FieldStringTest::ParamType> &info) { return info.param.field_.type().name(); });

TEST_P(FieldStringTest, ) {
    auto [field, expected] = GetParam();

    auto actual = UiTools::toString(field);
    EXPECT_EQ(actual, expected);
}

INSTANTIATE_TEST_SUITE_P(
    UiTools, FieldConvertValueTest,
    ::testing::Values(FieldConvertValueTestParams{Field(FieldType::DATE, FIELD_NAME, DATE_VALUE), FieldType::STRING,
                                                  u"01.11.2025"},
                      FieldConvertValueTestParams{Field(FieldType::EXPIRATION_MONTH, FIELD_NAME, DATE_VALUE),
                                                  FieldType::STRING, u"11/25"},
                      FieldConvertValueTestParams{Field(FieldType::EXPIRATION_MONTH, FIELD_NAME, DATE_VALUE),
                                                  FieldType::CARD_TYPE, CreditCardType::MIR.ordinal()},
                      FieldConvertValueTestParams{Field(FieldType::STRING, FIELD_NAME, STRING_VALUE), FieldType::HIDDEN,
                                                  STRING_VALUE}),
    [](const testing::TestParamInfo<FieldConvertValueTest::ParamType> &info) {
        return info.param.field_.type().name() + "_to_" + info.param.newType_.get().name();
    });

TEST_P(FieldConvertValueTest, ) {
    auto [field, newType, expected] = GetParam();

    auto actual = UiTools::convertValue(field, newType);
    EXPECT_EQ(actual, expected);
}
