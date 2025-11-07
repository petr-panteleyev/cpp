//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "generator.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include <QIcon>
#include <QTranslator>
#include <iostream>

namespace {

constexpr int DEFAULT_PASSWORD_LENGTH{16};

const std::string USAGE_MESSAGE = R"(Password Generator v25.10.2
© 2024-2025, Petr Panteleyev
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

std::unordered_map<pwdgen::PasswordGeneratorError, std::string> ERROR_MESSAGES{
    {pwdgen::PasswordGeneratorError::LENGTH_TOO_SMALL, "Password length is invalid"},
    {pwdgen::PasswordGeneratorError::NO_CHARACTER_SET, "At least one character set must be selected"},
};

pwdgen::PasswordGeneratorOptions buildOptions(const std::span<std::string> &arguments) {
    pwdgen::PasswordGeneratorOptions options = {false, false, false, false, DEFAULT_PASSWORD_LENGTH};

    for (auto it = std::next(arguments.begin()); it < arguments.end(); ++it) {
        if (*it == "--help") {
            throw USAGE_MESSAGE;
        }
        if (*it == "--unix") {
            return pwdgen::UNIX_OPTIONS;
        }
        if (*it == "--pin") {
            return pwdgen::PIN_OPTIONS;
        }
        if (*it == "--medium") {
            return pwdgen::MEDIUM_OPTIONS;
        }
        if (*it == "--long") {
            return pwdgen::LONG_OPTIONS;
        }
        if (*it == "-n") {
            if (++it == arguments.end()) {
                throw std::string("Length argument expects number.");
            } else {
                int length = std::stoi(*it);
                if (length < pwdgen::MIN_PASSWORD_LENGTH) {
                    throw pwdgen::PasswordGeneratorException(pwdgen::PasswordGeneratorError::LENGTH_TOO_SMALL);
                } else {
                    options.length = length;
                }
            }
        } else {
            if (!it->starts_with('-')) {
                throw "Unrecognized argument: " + *it;
            }
            for (auto char_it = std::next(it->begin()); char_it < it->end(); ++char_it) {
                switch (*char_it) {
                    case 'u': options.useUpperCase = true; break;
                    case 'l': options.useLowerCase = true; break;
                    case 'd': options.useDigits = true; break;
                    case 's': options.useSymbols = true; break;
                    default: throw std::string("Invalid option -") + *char_it;
                }
            }
        }
    }

    return options;
}

} // namespace

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    const auto uiLanguages = QLocale::system().uiLanguages();
    for (const auto &locale : uiLanguages) {
        const auto baseName = "password_generator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    std::vector<std::string> arguments;
    for (auto str : QCoreApplication::arguments()) {
        arguments.push_back(str.toStdString());
    }

    if (arguments.size() == 1) {
        a.setWindowIcon(QIcon(":images/icon.png"));

        MainWindow w;
        w.show();
        return a.exec();
    } else {
        try {
            auto options = buildOptions(arguments);
            std::cout << generate(options) << std::endl;
        } catch (const pwdgen::PasswordGeneratorException &ex) {
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
    return -1;
}
