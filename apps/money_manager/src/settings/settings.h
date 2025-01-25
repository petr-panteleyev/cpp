//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SETTINGS_H
#define SETTINGS_H

class QWidget;

namespace Settings {

void saveWindowDimensions(const QWidget *widget);
void loadWindowDimensions(QWidget *widget);

} // namespace Settings

#endif // SETTINGS_H
