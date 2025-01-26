//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "decimal.h"
#include "arithmeticexception.h"
#include <gtest/gtest.h>

using namespace Common;

template <typename T> static void testDecimalCtor(T value, DecimalBits bits, int scale, int signum) {
    Decimal actual{value};
    EXPECT_EQ(actual.bits(), bits);
    EXPECT_EQ(actual.scale(), scale);
    EXPECT_EQ(actual.signum(), signum);
}

TEST(CommonDecimalTestSuite, Decimal_Ctor_Int) {
    testDecimalCtor(static_cast<int>(123), 123, 0, 1);
    testDecimalCtor(static_cast<int>(-123), 123, 0, -1);
    testDecimalCtor(static_cast<int>(0), 0, 0, 0);
}

TEST(CommonDecimalTestSuite, Decimal_Ctor_Long) {
    testDecimalCtor(static_cast<long>(123), 123, 0, 1);
    testDecimalCtor(static_cast<long>(-123), 123, 0, -1);
    testDecimalCtor(static_cast<long>(0), 0, 0, 0);
}

TEST(CommonDecimalTestSuite, Decimal_Ctor_String) {
    testDecimalCtor("123", 123, 0, 1);
    testDecimalCtor("12.3", 123, 1, 1);
    testDecimalCtor("-12.3", 123, 1, -1);
    testDecimalCtor("-12.300", 12300, 3, -1);
    testDecimalCtor("12.30", 1230, 2, 1);
    testDecimalCtor("0.000", 0, 3, 0);
}

TEST(CommonDecimalTestSuite, Decimal_Ctor_String_Throws) {
    EXPECT_THROW(testDecimalCtor("--123", 123, 0, 1), ArithmeticException);
    EXPECT_THROW(testDecimalCtor("12-3", 123, 0, 1), ArithmeticException);
    EXPECT_THROW(testDecimalCtor("1.2.3", 123, 0, 1), ArithmeticException);
}

static void testAdd(const Decimal &x, const Decimal &y, const Decimal &expected) {
    EXPECT_EQ(x + y, expected);
    EXPECT_EQ(y + x, expected);
    EXPECT_EQ(x.add(y), expected);
    EXPECT_EQ(y.add(x), expected);
}

TEST(CommonDecimalTestSuite, Decimal_Add) {
    testAdd(Decimal("1.23"), Decimal("12.345"), Decimal("13.575"));
    testAdd(Decimal("-1.23"), Decimal("-12.345"), Decimal("-13.575"));
    testAdd(Decimal("1.23"), Decimal("-12.345"), Decimal("-11.115"));
    testAdd(Decimal("-1.23"), Decimal("12.345"), Decimal("11.115"));
    testAdd(Decimal("0.001"), Decimal("0.01"), Decimal("0.011"));
    testAdd(Decimal("1.001"), Decimal("0.01"), Decimal("1.011"));
}

static void testSubtract(const Decimal &x, const Decimal &y, const Decimal &expected) {
    EXPECT_EQ(x - y, expected);
    EXPECT_EQ(y - x, expected.negate());
    EXPECT_EQ(x.subtract(y), expected);
    EXPECT_EQ(y.subtract(x), expected.negate());
}

TEST(CommonDecimalTestSuite, Decimal_Subtract) {
    testSubtract(Decimal("1.23"), Decimal("12.345"), Decimal("-11.115"));
    testSubtract(Decimal("-1.23"), Decimal("-12.345"), Decimal("11.115"));
    testSubtract(Decimal("1.23"), Decimal("-12.345"), Decimal("13.575"));
    testSubtract(Decimal("-1.23"), Decimal("12.345"), Decimal("-13.575"));
    testSubtract(Decimal("0.001"), Decimal("0.01"), Decimal("-0.009"));
    testSubtract(Decimal("1.001"), Decimal("0.01"), Decimal("0.991"));
}

static void testMultiply(const Decimal &x, const Decimal &y, const Decimal &expected) {
    EXPECT_EQ(x * y, expected);
    EXPECT_EQ(y * x, expected);
    EXPECT_EQ(x.multiply(y), expected);
    EXPECT_EQ(y.multiply(x), expected);
}

TEST(CommonDecimalTestSuite, Decimal_Multiply) {
    testMultiply(Decimal(11), Decimal(11), Decimal(121));
    testMultiply(Decimal("1.23"), Decimal("12.345"), Decimal("15.18435"));
    testMultiply(Decimal("-1.23"), Decimal("-12.345"), Decimal("15.18435"));
    testMultiply(Decimal("1.23"), Decimal("-12.345"), Decimal("-15.18435"));
    testMultiply(Decimal("-1.23"), Decimal("12.345"), Decimal("-15.18435"));
    testMultiply(Decimal("10.000"), Decimal("12.345"), Decimal("123.450000"));
    testMultiply(Decimal("10"), Decimal("12.345"), Decimal("123.450"));
    testMultiply(Decimal("0"), Decimal("12.345"), Decimal("0.000"));
    testMultiply(Decimal("0.000"), Decimal("-12.345"), Decimal("0.000000"));
    testMultiply(Decimal("0.001"), Decimal("0.01"), Decimal("0.00001"));
}

static void testDivide(const Decimal &x, const Decimal &y, RoundingMode mode, const Decimal &expected) {
    EXPECT_EQ(x.divide(y, mode), expected);
}

TEST(CommonDecimalTestSuite, Decimal_Divide_HALF_UP) {
    testDivide(Decimal("10"), Decimal("10"), RoundingMode::HALF_UP, Decimal("1"));
    testDivide(Decimal("4.56"), Decimal("2.0000"), RoundingMode::HALF_UP, Decimal("2.28"));
    testDivide(Decimal("4.56"), Decimal("2"), RoundingMode::HALF_UP, Decimal("2.28"));
    testDivide(Decimal("1.23"), Decimal("2"), RoundingMode::HALF_UP, Decimal("0.62"));
    testDivide(Decimal("-1.23"), Decimal("2"), RoundingMode::HALF_UP, Decimal("-0.62"));
    testDivide(Decimal("10.00"), Decimal("3"), RoundingMode::HALF_UP, Decimal("3.33"));
    testDivide(Decimal("10.01"), Decimal("3"), RoundingMode::HALF_UP, Decimal("3.34"));
}

static void testToString(const Decimal &x, const std::string &expected) {
    EXPECT_EQ(x.toString(), expected);
}

TEST(CommonDecimalTestSuite, Decimal_ToString) {
    testToString(Decimal("1.230"), "1.230");
    testToString(Decimal("-1.23"), "-1.23");
    testToString(Decimal(123), "123");
    testToString(Decimal(-123), "-123");
    testToString(Decimal(12345, 2, 1), "123.45");
    testToString(Decimal(12345, 2, -1), "-123.45");
    testToString(Decimal(1, 3, 1), "0.001");
    testToString(Decimal(1001, 3, 1), "1.001");
}

static void testSetScale(const Decimal &x, int scale, const Decimal &expected) {
    EXPECT_EQ(x.setScale(scale), expected);
}

TEST(CommonDecimalTestSuite, Decimal_SetScale) {
    testSetScale(Decimal("123"), 2, Decimal("123.00"));
    testSetScale(Decimal("1.23"), 2, Decimal("1.23"));
    testSetScale(Decimal("1.23"), 5, Decimal("1.23000"));
    testSetScale(Decimal("0.01"), 3, Decimal("0.010"));
    testSetScale(Decimal("1.23000"), 2, Decimal("1.23"));
}

static void testSetScale(const Decimal &x, int scale, RoundingMode mode, const Decimal &expected) {
    EXPECT_EQ(x.setScale(scale, mode), expected);
}

TEST(CommonDecimalTestSuite, Decimal_SetScale_with_mode) {
    // HALF_UP
    testSetScale(Decimal("1.234"), 2, RoundingMode::HALF_UP, Decimal("1.23"));
    testSetScale(Decimal("1.235"), 2, RoundingMode::HALF_UP, Decimal("1.24"));
    testSetScale(Decimal("1.236"), 2, RoundingMode::HALF_UP, Decimal("1.24"));
}
