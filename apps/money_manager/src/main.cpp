//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.h"
#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":images/icon.png"));

    QApplication::setOrganizationDomain("panteleyev.org");
    QApplication::setApplicationName("MoneyManager");

    MainWindow w;
    w.show();
    return a.exec();
}
