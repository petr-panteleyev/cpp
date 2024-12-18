/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "generator.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>

using namespace pwdgen;

static const int DEFAULT_PASSWORD_LENGTH = 16;

static PasswordGeneratorOptions build_options(const QStringList &arguments);

static const std::string USAGE_MESSAGE = R"(Password Generator v24.11.1
(c) 2024, Petr Panteleyev
Usage:
  -u        - use upper case letters
  -l        - use lower case letters
  -d        - use digits
  -s        - use symbols
  -n <n>    - password length, default: 16, minimum length: 4
  --pin     - PIN: -d -n 4
  --unix    - Unix password: -ulds -n 8
  --medium  - medium password: -ulds -n 16
  --long    - long password: -ulds -n 32
  --help    - print this help message and exit
)";

static std::map<PasswordGeneratorError, std::string> ERROR_MESSAGES{
    {PasswordGeneratorError::LENGTH_TOO_SMALL, "Password length is invalid"},
    {PasswordGeneratorError::NO_CHARACTER_SET, "At least one character set must be selected"},
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto arguments = QCoreApplication::arguments();
    if (arguments.size() == 1) {
        a.setWindowIcon(QIcon(":images/icon.png"));

        QTranslator       translator;
        const auto uiLanguages = QLocale::system().uiLanguages();
        for (const auto &locale : uiLanguages) {
            const auto baseName = "password_generator_" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        try {
            auto options = build_options(arguments);
            std::cout << generate(options) << std::endl;
        } catch (const PasswordGeneratorException &ex) {
            std::cerr << ERROR_MESSAGES[ex.errorCode()] << std::endl;
            return -1;
        } catch (const std::string &message) {
            std::cerr << message << std::endl;
            return -1;
        } catch (const QString &message) {
            std::cerr << message.toStdString() << std::endl;
            return -1;
        }
    }
}

static int as_number(const QString &arg) {
    bool ok;
    int  result = arg.toInt(&ok);
    return ok ? result : -1;
}

static PasswordGeneratorOptions build_options(const QStringList &arguments) {
    PasswordGeneratorOptions options = {false, false, false, false, DEFAULT_PASSWORD_LENGTH};

    for (auto it = std::next(arguments.begin()); it < arguments.end(); ++it) {
        if (*it == "--help") {
            throw USAGE_MESSAGE;
        }
        if (*it == "--unix") {
            return UNIX_OPTIONS;
        }
        if (*it == "--pin") {
            return PIN_OPTIONS;
        }
        if (*it == "--medium") {
            return MEDIUM_OPTIONS;
        }
        if (*it == "--long") {
            return LONG_OPTIONS;
        }
        if (*it == "-n") {
            if (++it == arguments.end()) {
                throw std::string("Length argument expects number.");
            } else {
                int length = as_number(*it);
                if (length < MIN_PASSWORD_LENGTH) {
                    throw PasswordGeneratorException(PasswordGeneratorError::LENGTH_TOO_SMALL);
                } else {
                    options.length = length;
                }
            }
        } else {
            if (!it->startsWith('-')) {
                throw "Unrecognized argument: " + *it;
            }
            for (auto char_it = std::next(it->begin()); char_it < it->end(); ++char_it) {
                char ch = char_it->toLatin1();
                switch (ch) {
                    case 'u': options.useUpperCase = true; break;
                    case 'l': options.useLowerCase = true; break;
                    case 'd': options.useDigits = true; break;
                    case 's': options.useSymbols = true; break;
                    default: throw std::string("Invalid option -") + ch;
                }
            }
        }
    }

    return options;
}
