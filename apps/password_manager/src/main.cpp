//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "serializer.hpp"
#include "str.h"
#include "translations.h"
#include "ui/mainwindow.h"
#include <QApplication>
#include <xercesc/util/PlatformUtils.hpp>

int main(int argc, char *argv[]) {
    xercesc::XMLPlatformUtils::Initialize();
    Serializer::initialize();

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":images/icon.png"));

    // a.setStyleSheet("QTableView{font: \"Courier New\";font-size:24px}");

    QApplication::setOrganizationDomain("panteleyev.org");
    QApplication::setApplicationName(Str::APP_TITLE);

    Translations::initialize();
    MainWindow w;
    w.show();
    return a.exec();
}
