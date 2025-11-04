//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include "generator.h"

#include "ui_mainwindow.h"
#include <QApplication>
#include <QClipboard>
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include <iostream>

module apps.password_generator;
import :util;

namespace {

using namespace pwdgen;

std::unordered_map<PasswordGeneratorError, std::string> ERROR_MESSAGES{
    {PasswordGeneratorError::LENGTH_TOO_SMALL, "Password length is invalid"},
    {PasswordGeneratorError::NO_CHARACTER_SET, "At least one character set must be selected"},
};

} // namespace

namespace {

class MainWindow : public QMainWindow {
  public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
        ui->setupUi(this);

        // Setup length combobox
        for (auto length : PASSWORD_LENGTH_OPTIONS) {
            ui->lengthComboBox->addItem(QString::number(length), QVariant(length));
        }
        ui->lengthComboBox->setCurrentIndex(DEFAULT_LENGTH_INDEX);

        visualizeOptions(pwdgen::MEDIUM_OPTIONS);

        // Connect actions
        connect(ui->actionGenerate, &QAction::triggered, [this]() {
            generate(pwdgen::PasswordGeneratorOptions{
                ui->upperCaseCheck->isChecked(),
                ui->lowerCaseCheck->isChecked(),
                ui->digitsCheck->isChecked(),
                ui->symbolsCheck->isChecked(),
                ui->lengthComboBox->currentData().toInt(),
            });
        });
        connect(ui->actionExit, &QAction::triggered, [this]() { close(); });
        connect(ui->actionUNIX, &QAction::triggered, [this]() { generate(pwdgen::UNIX_OPTIONS); });
        connect(ui->actionPIN, &QAction::triggered, [this]() { generate(pwdgen::PIN_OPTIONS); });
        connect(ui->actionMedium_Password, &QAction::triggered, [this]() { generate(pwdgen::MEDIUM_OPTIONS); });
        connect(ui->actionLong_Password, &QAction::triggered, [this]() { generate(pwdgen::LONG_OPTIONS); });
        connect(ui->actionCopy, &QAction::triggered, [this]() {
            auto text = ui->passwordEdit->text();
            auto clipboard = QGuiApplication::clipboard();
            if (clipboard != nullptr && !text.isEmpty()) {
                clipboard->setText(text);
            }
        });
    }

    ~MainWindow() {}

  private:
    static constexpr std::array<int, 10> PASSWORD_LENGTH_OPTIONS = {4, 6, 8, 16, 24, 32, 40, 48, 56, 64};
    static constexpr int DEFAULT_LENGTH_INDEX = 3;

  private:
    void visualizeOptions(const pwdgen::PasswordGeneratorOptions &options) {
        ui->upperCaseCheck->setChecked(options.useUpperCase);
        ui->lowerCaseCheck->setChecked(options.useLowerCase);
        ui->digitsCheck->setChecked(options.useDigits);
        ui->symbolsCheck->setChecked(options.useSymbols);

        auto index = ui->lengthComboBox->findData(QVariant(options.length));
        ui->lengthComboBox->setCurrentIndex(index);
    }

    void generate(const pwdgen::PasswordGeneratorOptions &options) {
        visualizeOptions(options);

        try {
            ui->passwordEdit->setText(QString::fromStdString(pwdgen::generate(options)));
        } catch (pwdgen::PasswordGeneratorException &e) {
            ui->passwordEdit->setText("Ошибка");
        }
    }

  private:
    std::unique_ptr<Ui::MainWindow> ui;
};

} // namespace

int PasswordGeneratorApplication::main(int argc, char *argv[]) {
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
    return -1;
}
