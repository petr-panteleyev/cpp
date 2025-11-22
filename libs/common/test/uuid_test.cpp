//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "uuid.hpp"
#include <gtest/gtest.h>

TEST(UUIDTest, fromToString) {
    auto uuid = UUID::randomUuid();

    auto str = UUID::toStdString(uuid);
    EXPECT_EQ(str.size(), 36);

    auto restored = UUID::fromStdString(str);
    EXPECT_EQ(restored, uuid);
}
