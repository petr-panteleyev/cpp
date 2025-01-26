//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CURRENCYWINDOW_H
#define CURRENCYWINDOW_H

#include <QMainWindow>

namespace Ui {
class CurrencyWindow;
}

class MainWindow;

class CurrencyWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit CurrencyWindow(QWidget *parent);
    ~CurrencyWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    MainWindow *getMainWindow() const { return reinterpret_cast<MainWindow *>(parent()); };

  private:
    std::unique_ptr<Ui::CurrencyWindow> ui;

    class CurrencyFilterModel;
    std::unique_ptr<CurrencyFilterModel> model_;
};

#endif // CURRENCYWINDOW_H
