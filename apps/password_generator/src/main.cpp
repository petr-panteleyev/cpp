//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "generator.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include <QIcon>
#include <QTranslator>
#include <expected>
#include <iostream>

namespace {

constexpr int DEFAULT_PASSWORD_LENGTH{16};

const std::string USAGE_MESSAGE = R"(Password Generator v25.11.3
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

std::unordered_map<pwdgen::Error, std::string> ERROR_MESSAGES{
    {pwdgen::Error::LENGTH_TOO_SMALL, "Password length is invalid"},
    {pwdgen::Error::NO_CHARACTER_SET, "At least one character set must be selected"},
};

auto parseInt(const std::string &str) -> int {
    try {
        return std::stoi(str);
    } catch (...) {
        throw std::string{"Invalid length argument"};
    }
}

auto buildOptions(const std::span<std::string> &arguments) -> std::expected<pwdgen::Options, std::string> {
    pwdgen::Options options = {false, false, false, false, DEFAULT_PASSWORD_LENGTH};

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
                return std::unexpected("Length argument expects number.");
            } else {
                int length = parseInt(*it);
                if (length < pwdgen::MIN_PASSWORD_LENGTH) {
                    return std::unexpected(ERROR_MESSAGES[pwdgen::Error::LENGTH_TOO_SMALL]);
                } else {
                    options.length = length;
                }
            }
        } else {
            if (!it->starts_with('-')) {
                return std::unexpected("Unrecognized argument: " + *it);
            }
            for (auto char_it = std::next(it->begin()); char_it < it->end(); ++char_it) {
                switch (*char_it) {
                    case 'u': options.useUpperCase = true; break;
                    case 'l': options.useLowerCase = true; break;
                    case 'd': options.useDigits = true; break;
                    case 's': options.useSymbols = true; break;
                    default: return std::unexpected(std::string{"Invalid option -"} + *char_it);
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
        auto result = buildOptions(arguments).and_then([](const auto &options) {
            auto pwd = pwdgen::generate(options);
            return pwd ? std::expected<std::string, std::string>(pwd.value())
                       : std::unexpected(ERROR_MESSAGES[pwd.error()]);
        });
        if (result) {
            std::cout << result.value() << std::endl;
            return 0;
        } else {
            std::cerr << result.error() << std::endl;
            return -1;
        }
    }
}
