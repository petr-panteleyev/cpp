//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

class QWidget;

namespace Settings {

void saveWindowDimensions(const QWidget *widget);
void loadWindowDimensions(QWidget *widget);

} // namespace Settings
