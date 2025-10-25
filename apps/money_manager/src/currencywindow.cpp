//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "currencywindow.h"
#include "currency.h"
#include "datacache.h"
#include "mainwindow.h"
#include "settings.h"
#include "ui_currencywindow.h"
#include <QSortFilterProxyModel>

using std::make_unique;

namespace {

constexpr int COLUMN_NAME = 0;
constexpr int COLUMN_DESCRIPTION = 1;

constexpr int COLUMN_COUNT = COLUMN_DESCRIPTION + 1;

const std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_NAME, QHeaderView::ResizeToContents},
    {COLUMN_DESCRIPTION, QHeaderView::Stretch},
};

const std::array<QString, COLUMN_COUNT> COLUMN_NAMES{"Название", "Описание"};

} // namespace

class CurrencyWindow::CurrencyFilterModel final : public QSortFilterProxyModel {
  public:
    explicit CurrencyFilterModel() {}
    ~CurrencyFilterModel() {};

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMN_COUNT; }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole || section >= COLUMN_COUNT) {
            return QVariant();
        }
        return COLUMN_NAMES[section];
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        auto currency = DataCache::cache().getCurrency(mapToSource(index).row());
        switch (index.column()) {
            case COLUMN_NAME: return currency.symbol();
            case COLUMN_DESCRIPTION: return currency.description();
        }

        return QVariant();
    };
};

CurrencyWindow::CurrencyWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::CurrencyWindow>()}, model_{make_unique<CurrencyFilterModel>()} {
    ui->setupUi(this);

    getMainWindow()->setupWindowMenu(ui->menuWindow);

    model_->setSourceModel(DataCache::cache().getCurrencyItemModel());
    ui->currencyTableView->setModel(model_.get());

    auto header = ui->currencyTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });

    Settings::loadWindowDimensions(this);
}

CurrencyWindow::~CurrencyWindow() {
}

void CurrencyWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
