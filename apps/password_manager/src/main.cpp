/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "ui/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "translations.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":images/icon.png"));

    QTranslator       translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "password_manager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Translations::initialize();
    MainWindow w;
    w.show();
    return a.exec();
}
