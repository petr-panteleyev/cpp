//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <functional>
#include <mutex>
#include <stdexcept>
#include <unordered_map>

namespace Common {

using SubscriptionId = unsigned;

template <typename T>
    requires std::copy_constructible<T>
class ObservableValue final {
  public:
    explicit ObservableValue(const T &value) noexcept : value_{value} {}

    ObservableValue &operator=(const T &newValue) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (newValue != value_) {
            auto oldValue = value_;
            value_ = newValue;

            for (const auto &listener : listeners_) {
                listener.second(oldValue, newValue);
            }
        }
        return *this;
    }

    const T &get() const noexcept { return value_; }

    SubscriptionId subscribe(const std::function<void(const T &, const T &)> &listener) {
        std::lock_guard<std::mutex> lock(mutex_);
        listeners_[++id] = listener;
        return id;
    };

    void unsubscribe(SubscriptionId subscriptionId) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!listeners_.contains(subscriptionId)) {
            throw std::out_of_range("subscriptionId does not exist");
        }
        listeners_.erase(subscriptionId);
    }

  private:
    T value_;
    std::unordered_map<SubscriptionId, std::function<void(const T &, const T &)>> listeners_;
    std::mutex mutex_;

    static inline SubscriptionId id = 0;
};

} // namespace Common
