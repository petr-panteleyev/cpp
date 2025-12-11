//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.hpp"
#include "pictures.hpp"
#include "resources.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(Pictures::icon(Picture::ICON));

    QFontDatabase::addApplicationFontFromData(
        QByteArray(reinterpret_cast<const char *>(res::MINE_SWEEPER_FONT.bytes_), res::MINE_SWEEPER_FONT.size_));
    QFontDatabase::addApplicationFontFromData(
        QByteArray(reinterpret_cast<const char *>(res::PIXEL_LCD_7_FONT.bytes_), res::PIXEL_LCD_7_FONT.size_));

    QApplication::setOrganizationDomain("panteleyev.org");
    QApplication::setApplicationName("Sapper");

    MainWindow w;
    w.show();
    return a.exec();
}
