//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "settings.h"
#include "qthelpers.h"
#include <QSettings>

namespace Settings {

static const QString GROUP_WINDOWS{"windows"};

void saveWindowDimensions(const QWidget *widget) {
    QSettings settings;
    QtHelpers::saveWindowDimensions(*widget, settings, GROUP_WINDOWS);
}

void loadWindowDimensions(QWidget *widget) {
    QSettings settings;
    QtHelpers::loadWindowDimensions(*widget, settings, GROUP_WINDOWS);
}

} // namespace Settings
