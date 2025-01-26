//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "decimal.h"
#include "arithmeticexception.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <compare>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace {

static constexpr std::array<unsigned long, 19> POWERS_OF_TEN = {
    1L,
    10L,
    100L,
    1000L,
    10000L,
    100000L,
    1000000L,
    10000000L,
    100000000L,
    1000000000L,
    10000000000L,
    100000000000L,
    1000000000000L,
    10000000000000L,
    100000000000000L,
    1000000000000000L,
    10000000000000000L,
    100000000000000000L,
    1000000000000000000L,
};
static constexpr int POWERS_OF_TEN_SIZE = POWERS_OF_TEN.size();

template <typename T> int signum(T x) {
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

unsigned long pow10(int pow) {
    assert(pow >= 0);

    if (pow < POWERS_OF_TEN_SIZE) {
        return POWERS_OF_TEN[pow];
    }

    int result = 1;
    for (auto i = 0; i < pow; ++i) {
        result *= 10;
    }
    return result;
}

Common::DecimalBits normalize(const Common::Decimal &x, int maxScale) {
    auto scaleDiff = maxScale - x.scale();
    auto bits = x.bits();
    return bits * pow10(scaleDiff);
}

bool needIncrement(Common::RoundingMode mode, int resultSignum, std::strong_ordering halfCompare, bool resultIsOdd) {
    switch (mode) {
        case Common::RoundingMode::ROUND_DOWN: return false;
        default: {
            if (halfCompare == std::strong_ordering::less) {
                return false;
            } else if (halfCompare == std::strong_ordering::greater) {
                return true;
            } else {
                switch (mode) {
                    case Common::RoundingMode::HALF_UP: return true;
                    default: throw std::runtime_error("Unexpected rounding mode");
                }
            }
        }
    }
}

bool needIncrement(Common::DecimalBits divisor, Common::RoundingMode roundingMode, int resultSignum,
                   Common::DecimalBits result, Common::DecimalBits remainder) {
    return needIncrement(roundingMode, resultSignum, 2 * remainder <=> divisor, (result & 1L) != 0L);
}

Common::Decimal divideAndRound(Common::DecimalBits dividend, Common::DecimalBits divisor, int scale, int signum,
                               Common::RoundingMode mode) {
    auto result = dividend / divisor;
    if (mode == Common::RoundingMode::ROUND_DOWN) {
        return Common::Decimal(result, scale, signum);
    }

    auto remainder = dividend % divisor;

    if (remainder != 0 && needIncrement(divisor, mode, signum, result, remainder)) {
        ++result;
    }

    return Common::Decimal(result, scale, signum);
}

} // namespace

namespace Common {

Decimal::Decimal(int intValue) noexcept {
    signum_ = ::signum(intValue);
    bits_ = static_cast<DecimalBits>(std::abs(intValue));
    scale_ = 0;
}

Decimal::Decimal(long longValue) noexcept {
    signum_ = ::signum(longValue);
    bits_ = static_cast<DecimalBits>(std::abs(longValue));
    scale_ = 0;
}

Decimal::Decimal(const std::string &stringValue) : stringValue_{stringValue} {
    if (stringValue.empty()) {
        throw ArithmeticException("Decimal value string cannot be empty");
    }

    int start = 0;
    if (stringValue[0] == '-') {
        start = 1;
        signum_ = -1;
    } else {
        signum_ = 1;
    }

    bits_ = 0;
    scale_ = 0;
    bool hasDot = false;

    std::for_each(std::next(stringValue.begin(), start), stringValue.end(), [&](auto ch) {
        if (ch == '.') {
            if (hasDot) {
                throw ArithmeticException("Decimal value string contains more than 1 dot");
            }
            hasDot = true;
        } else if (!std::isdigit(ch)) {
            throw ArithmeticException("Decimal value string contains non digit character");
        } else {
            bits_ = bits_ * 10 + ch - '0';
            if (hasDot) {
                ++scale_;
            }
        }
    });

    if (bits_ == 0) {
        signum_ = 0;
    }
}

std::strong_ordering Decimal::operator<=>(const Decimal &that) const noexcept {
    if (scale_ == that.scale_) {
        return signum_ * bits_ <=> that.signum_ * that.bits_;
    }

    auto maxScale = std::max(scale_, that.scale_);
    auto normThis = normalize(*this, maxScale);
    auto normThat = normalize(that, maxScale);
    return signum_ * normThis <=> that.signum_ * normThat;
}

std::string Decimal::toString() const noexcept {
    if (!stringValue_.empty()) {
        return stringValue_;
    }

    auto signStr = signum_ < 0 ? "-" : "";
    auto str = std::to_string(bits_);
    auto strSize = static_cast<int>(str.size());
    if (scale_ > 0) {
        if (scale_ >= strSize) {
            std::string prep{"0."};
            for (auto i = 0; i < scale_ - strSize; ++i) {
                prep.push_back('0');
            }
            str = prep + str;
        } else {
            str.insert(std::next(str.begin(), str.size() - scale_), '.');
        }
    }
    return signStr + str;
}

Decimal Decimal::divide(const Decimal &x, RoundingMode mode) const {
    auto scale = scale_ + x.scale_;
    auto nThis = ::normalize(*this, scale);

    auto signum = this->signum_ * x.signum_;

    return divideAndRound(nThis, x.bits_, scale_, signum, mode);
}

Decimal Decimal::setScale(int scale) const {
    if (scale == scale_) {
        return Decimal(*this);
    }

    auto scaleDiff = scale - scale_;
    int multiplier = pow10(std::abs(scaleDiff));
    if (scaleDiff > 0) {
        return Decimal(bits_ * multiplier, scale, signum_);
    } else {
        auto remainder = bits_ % multiplier;
        if (remainder != 0) {
            throw ArithmeticException("setScale requires rounding");
        }
        return Decimal(bits_ / multiplier, scale, signum_);
    }
}

Decimal Decimal::setScale(int scale, RoundingMode mode) const {
    if (scale == scale_) {
        return Decimal(*this);
    }

    if (scale > scale_ || mode == RoundingMode::UNNECESSARY) {
        return setScale(scale);
    }

    int multiplier = pow10(scale_ - scale);
    return divideAndRound(bits_, multiplier, scale, signum_, mode);
}

Decimal operator+(const Decimal &x, const Decimal &y) noexcept {
    auto maxScale = std::max(x.scale_, y.scale_);
    auto nX = ::normalize(x, maxScale);
    auto nY = ::normalize(y, maxScale);

    if (x.signum() == y.signum()) {
        return Decimal(nX + nY, maxScale, x.signum());
    } else {
        if (nX > nY) {
            return Decimal(nX - nY, maxScale, x.signum());
        } else {
            return Decimal(nY - nX, maxScale, y.signum());
        }
    }
}

Decimal operator*(const Decimal &x, const Decimal &y) noexcept {
    auto result = Decimal(x.bits_ * y.bits_, x.scale_ + y.scale_, x.signum_ * y.signum_);
    return Decimal(result);
}

} // namespace Common
