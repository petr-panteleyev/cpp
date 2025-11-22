//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "field.hpp"
#include <QString>

namespace UiTools {

[[nodiscard]] QString toString(const Field &field) noexcept;
[[nodiscard]] Field::FieldValue convertValue(const Field &field, const FieldType &newType) noexcept;

} // namespace UiTools
