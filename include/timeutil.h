//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <chrono>
#include <ctime>

namespace TimeUtil {

inline unsigned long currentTimeMillis() {
    auto epoch = std::chrono::system_clock::now().time_since_epoch();
    return static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count());
}

} // namespace TimeUtil
