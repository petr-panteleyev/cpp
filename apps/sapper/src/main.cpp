//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.hpp"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":images/icon.png"));

    QFontDatabase::addApplicationFont(":/fonts/mine-sweeper.ttf");
    QFontDatabase::addApplicationFont(":/fonts/neat-lcd.ttf");

    QApplication::setOrganizationDomain("panteleyev.org");
    QApplication::setApplicationName("Sapper");

    MainWindow w;
    w.show();
    return a.exec();
}
