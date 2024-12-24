//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef QTHELPERS_H
#define QTHELPERS_H

#include <QAction>
#include <QComboBox>
#include <QMenu>
#include <QWidget>
#include <initializer_list>

namespace QtHelpers {

inline void addActions(QWidget *widget, std::initializer_list<QAction *> actions) {
    for (auto p : actions) {
        widget->addAction(p);
    }
}

inline void addActions(QMenu *menu, std::initializer_list<QAction *> actions) {
    for (auto p : actions) {
        if (p == nullptr) {
            menu->addSeparator();
        } else {
            menu->addAction(p);
        }
    }
}

inline void enableActions(bool enabled, std::initializer_list<QAction *> actions) {
    for (auto p : actions) {
        p->setEnabled(enabled);
    }
}

inline int indexOfData(const QComboBox &comboBox, const QVariant &data, int role = Qt::UserRole) {
    for (auto index = 0; index < comboBox.count(); ++index) {
        if (comboBox.itemData(index, role) == data) {
            return index;
        }
    }
    return -1;
}

} // namespace QtHelpers

#endif
