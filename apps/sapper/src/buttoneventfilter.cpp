//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "buttoneventfilter.h"
#include "mainwindow.h"
#include <QEvent>

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
