//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":images/icon.png"));

    QFontDatabase::addApplicationFont(":/fonts/mine-sweeper.ttf");
    QFontDatabase::addApplicationFont(":/fonts/neat-lcd.ttf");

    QApplication::setOrganizationDomain("panteleyev.org");
    QApplication::setApplicationName("Sapper");

    QTranslator       translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "sapper_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
