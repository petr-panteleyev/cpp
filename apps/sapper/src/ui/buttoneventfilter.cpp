//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "buttoneventfilter.hpp"
#include "mainwindow.hpp"
#include <QEvent>
#include <QPushButton>

bool ButtonEventFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) {
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        if (!disabled_) {
            auto mainWindow = reinterpret_cast<MainWindow *>(this->parent());
            mainWindow->onButtonClicked(reinterpret_cast<QPushButton *>(obj), reinterpret_cast<QMouseEvent *>(event));
        }
        return true;
    }

    return QObject::eventFilter(obj, event);
}
