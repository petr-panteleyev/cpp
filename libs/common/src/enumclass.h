//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ENUMCLASS_H
#define ENUMCLASS_H

#include <stdexcept>
#include <string>
#include <vector>

namespace Common {

template <typename T> class EnumClass {
  public:
    unsigned ordinal() const noexcept { return ordinal_; }
    const std::string &name() const noexcept { return name_; }

    bool operator==(const EnumClass &that) const noexcept { return this->ordinal_ == that.ordinal_; }

    int operator<=>(const EnumClass &that) const noexcept {
        if (this->ordinal_ < that.ordinal_)
            return -1;
        if (this->ordinal_ > that.ordinal_)
            return 1;
        return 0;
    }

  public:
    virtual ~EnumClass() = default;

    static const std::vector<std::reference_wrapper<const T>> &values() noexcept { return values_; }

    static const T &valueOf(const std::string &name) {
        for (const T &v : values()) {
            if (v.name() == name) {
                return v;
            }
        }
        throw std::out_of_range("::" + name + " is not defined");
    }

    static const T &valueOf(unsigned ordinal) { return values_.at(ordinal); }

  protected:
    explicit EnumClass(const std::string &name) noexcept : ordinal_{nextOrdinal_++}, name_{name} {}

  private:
    EnumClass(const EnumClass &) = delete;
    EnumClass(const EnumClass &&) = delete;

  private:
    const unsigned ordinal_;
    const std::string name_;

    static inline unsigned nextOrdinal_ = 0;

    static const std::vector<std::reference_wrapper<const T>> values_;
};

} // namespace Common

#endif // ENUMCLASS_H
