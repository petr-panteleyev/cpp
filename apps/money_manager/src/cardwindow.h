//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QMainWindow>

namespace Ui {
class CardWindow;
}

class MainWindow;

class CardWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit CardWindow(QWidget *parent);
    ~CardWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    MainWindow *getMainWindow() const { return reinterpret_cast<MainWindow *>(parent()); };

  private:
    std::unique_ptr<Ui::CardWindow> ui;

    class CardFilterModel;
    std::unique_ptr<CardFilterModel> model_;
};
