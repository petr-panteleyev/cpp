//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <boost/uuid.hpp>

namespace UUID {

using UUID = boost::uuids::uuid;

inline UUID randomUuid() {
    return boost::uuids::random_generator()();
}

inline std::string randomUuidString() {
    return boost::uuids::to_string(randomUuid());
}

inline std::string toStdString(const UUID &uuid) {
    return boost::uuids::to_string(uuid);
}

inline UUID fromStdString(const std::string_view &s) {
    return boost::uuids::string_generator()(s.begin(), s.end());
}

} // namespace UUID
