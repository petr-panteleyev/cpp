/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QWidget>

namespace ui {

template <typename T>
concept Widget = std::derived_from<T, QWidget>;

template <typename T>
concept Menu = std::derived_from<T, QMenu>;

template <typename T>
concept Action = std::derived_from<T, QAction>;

template <Widget W, Action... A> void addActions(W *widget, A *...actions) {
    for (auto p : {actions...}) {
        widget->addAction(p);
    }
}

constexpr QAction *separator = nullptr;

template <Menu M, Action... A> void addMenuActions(M *menu, A *...actions) {
    for (auto p : {actions...}) {
        if (p == nullptr) {
            menu->addSeparator();
        } else {
            menu->addAction(p);
        }
    }
}

} // namespace ui

#endif // TEMPLATES_H
