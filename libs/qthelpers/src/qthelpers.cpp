//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "qthelpers.h"
#include <QAction>
#include <QComboBox>
#include <QMenu>
#include <QSettings>
#include <QWidget>

namespace QtHelpers {

void addActions(QWidget *widget, std::initializer_list<QAction *> actions) {
    for (auto p : actions) {
        widget->addAction(p);
    }
}

void addActions(QMenu *menu, std::initializer_list<QAction *> actions) {
    for (auto p : actions) {
        if (p == nullptr) {
            menu->addSeparator();
        } else {
            menu->addAction(p);
        }
    }
}

void enableActions(bool enabled, std::initializer_list<QAction *> actions) {
    for (auto p : actions) {
        p->setEnabled(enabled);
    }
}

int indexOfData(const QComboBox &comboBox, const QVariant &data, int role) {
    for (auto index = 0; index < comboBox.count(); ++index) {
        if (comboBox.itemData(index, role) == data) {
            return index;
        }
    }
    return -1;
}

void saveWindowDimensions(const QWidget &widget, QSettings &settings, const QString &group) {
    settings.beginGroup(group);

    settings.beginGroup(widget.objectName());
    settings.setValue("size", widget.size());
    settings.setValue("position", widget.pos());
    settings.setValue("maximized", widget.isMaximized());
    settings.endGroup();

    settings.endGroup();
}

void loadWindowDimensions(QWidget &widget, QSettings &settings, const QString &group) {
    settings.beginGroup(group);

    settings.beginGroup(widget.objectName());
    auto maximized = settings.value("maximized").toBool();
    if (maximized) {
        widget.showMaximized();
    } else {
        auto position = settings.value("position").toPoint();
        if (!position.isNull()) {
            widget.move(position);
        }
        auto size = settings.value("size").toSize();
        if (size.isValid()) {
            widget.resize(settings.value("size").toSize());
        }
    }

    settings.endGroup();
}

} // namespace QtHelpers
