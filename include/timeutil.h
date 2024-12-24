//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <chrono>

namespace TimeUtil {

inline unsigned long currentTimeMillis() {
    auto epoch = std::chrono::system_clock::now().time_since_epoch();
    return static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count());
}

} // namespace TimeUtil

#endif // TIMEUTIL_H
