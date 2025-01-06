//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef DECIMAL_H
#define DECIMAL_H

#include <compare>
#include <string>

namespace Common {

using DecimalBits = unsigned long long;

enum class RoundingMode { ROUND_DOWN, HALF_UP, UNNECESSARY };

class Decimal final {
  public:
    static const Decimal ZERO;
    static const Decimal ONE;
    static const Decimal TEN;

  public:
    explicit Decimal(int intValue) noexcept;
    explicit Decimal(long longValue) noexcept;
    explicit Decimal(const std::string &stringValue);
    explicit Decimal(DecimalBits bits, int scale, int signum) noexcept : bits_{bits}, scale_{scale}, signum_{signum} {}

    Decimal(const Decimal &x) noexcept : bits_{x.bits_}, scale_{x.scale_}, signum_{x.signum_} {}
    ~Decimal() = default;

    bool operator==(const Decimal &that) const noexcept {
        return this->bits_ == that.bits_ && this->scale_ == that.scale_ && this->signum_ == that.signum_;
    }

    std::strong_ordering operator<=>(const Decimal &that) noexcept;

    DecimalBits bits() const noexcept { return bits_; }
    int signum() const noexcept { return signum_; }
    int scale() const noexcept { return scale_; }

    std::string toString() const noexcept;

    [[nodiscard]] Decimal abs() const noexcept { return Decimal(bits_, scale_, signum_ == -1 ? 1 : signum_); }
    [[nodiscard]] Decimal negate() const noexcept { return Decimal(bits_, scale_, -signum_); }

    friend Decimal operator+(const Decimal &x, const Decimal &y) noexcept;
    [[nodiscard]] Decimal add(const Decimal &x) const noexcept { return *this + x; }

    friend Decimal operator-(const Decimal &x, const Decimal &y) noexcept { return x + y.negate(); }
    [[nodiscard]] Decimal subtract(const Decimal &x) const noexcept { return *this - x; }

    friend Decimal operator*(const Decimal &x, const Decimal &y) noexcept;
    [[nodiscard]] Decimal multiply(const Decimal &x) const noexcept { return *this * x; }

    [[nodiscard]] Decimal divide(const Decimal &x, RoundingMode mode) const;

    [[nodiscard]] Decimal setScale(int scale) const;
    [[nodiscard]] Decimal setScale(int scale, RoundingMode mode) const;

  private:
    DecimalBits bits_;
    int scale_;
    int signum_;
    std::string stringValue_;
};

const inline Decimal Decimal::ZERO{0};
const inline Decimal Decimal::ONE{1};
const inline Decimal Decimal::TEN{10};

} // namespace Common

#endif // DECIMAL_H
