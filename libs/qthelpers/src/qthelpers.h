//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef QTHELPERS_H
#define QTHELPERS_H

#include <initializer_list>

class QAction;
class QComboBox;
class QVariant;
class QMenu;
class QSettings;
class QString;
class QWidget;

namespace QtHelpers {

void addActions(QWidget *widget, std::initializer_list<QAction *> actions);
void addActions(QMenu *menu, std::initializer_list<QAction *> actions);
void enableActions(bool enabled, std::initializer_list<QAction *> actions);

int indexOfData(const QComboBox &comboBox, const QVariant &data, int role);

void saveWindowDimensions(const QWidget &widget, QSettings &settings, const QString &group);
void loadWindowDimensions(QWidget &widget, QSettings &settings, const QString &group);

} // namespace QtHelpers

#endif
