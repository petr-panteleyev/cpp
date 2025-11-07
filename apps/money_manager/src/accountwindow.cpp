//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "accountwindow.h"
#include "account.h"
#include "currency.h"
#include "datacache.h"
#include "decimal.hpp"
#include "mainwindow.h"
#include "moneyrecorditemmodel.h"
#include "translation.h"
#include "ui_accountwindow.h"
#include <QSortFilterProxyModel>
#include <compare>
#include <settings.h>
#include <unordered_map>

using Common::Decimal;
using Common::RoundingMode;
using std::make_unique;

namespace {

const QColor NEGATIVE_COLOR{255, 0, 0};
const QColor POSITIVE_COLOR{0, 128, 0};

constexpr int COLUMN_NAME = 0;
constexpr int COLUMN_CATEGORY = 1;
constexpr int COLUMN_CURRENCY = 2;
constexpr int COLUMN_INTEREST = 3;
constexpr int COLUMN_CLOSING = 4;
constexpr int COLUMN_COMMENT = 5;
constexpr int COLUMN_BALANCE = 6;
constexpr int COLUMN_WAITING = 7;

constexpr int COLUMN_COUNT = COLUMN_WAITING + 1;

const std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_NAME, QHeaderView::ResizeToContents},     {COLUMN_CATEGORY, QHeaderView::ResizeToContents},
    {COLUMN_CURRENCY, QHeaderView::ResizeToContents}, {COLUMN_INTEREST, QHeaderView::ResizeToContents},
    {COLUMN_CLOSING, QHeaderView::ResizeToContents},  {COLUMN_COMMENT, QHeaderView::Stretch},
    {COLUMN_BALANCE, QHeaderView::ResizeToContents},  {COLUMN_WAITING, QHeaderView::ResizeToContents}};

const std::array<QString, COLUMN_COUNT> COLUMN_NAMES{"Название", "Категория",   "Валюта", "%%",
                                                     "До",       "Комментарий", "Баланс", "Ожидает"};

} // namespace

class AccountWindow::AccountFilterModel : public QSortFilterProxyModel {
  public:
    explicit AccountFilterModel() {}
    ~AccountFilterModel() {};

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMN_COUNT; };

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole || section >= COLUMN_COUNT) {
            return QVariant();
        }
        return COLUMN_NAMES[section];
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid()) {
            return QVariant();
        }

        int row = mapToSource(index).row();
        auto account = DataCache::cache().getAccount(row);

        switch (index.column()) {
            case COLUMN_NAME:
                if (role == Qt::DisplayRole) {
                    return account.name();
                }
                break;
            case COLUMN_CATEGORY:
                if (role == Qt::DisplayRole) {
                    return Translation::translateCategoryType(account.type());
                }
                break;
            case COLUMN_CURRENCY:
                if (role == Qt::DisplayRole) {
                    if (account.currencyUuid().has_value()) {
                        auto currency = DataCache::cache().getCurrency(account.currencyUuid().value());
                        return currency.symbol();
                    } else {
                        return "";
                    }
                }
                break;
            case COLUMN_INTEREST:
                if (role == Qt::DisplayRole) {
                    if (account.interest() <=> Decimal::ZERO == std::strong_ordering::equal) {
                        return "";
                    } else {
                        return QString::fromStdString(account.interest().setScale(2, RoundingMode::HALF_UP).toString());
                    }
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                }
                break;
            case COLUMN_CLOSING:
                if (role == Qt::DisplayRole) {
                    return account.closingDate().has_value() ? account.closingDate().value().toString("dd.MM.yyyy")
                                                             : "";
                }
                break;
            case COLUMN_COMMENT:
                if (role == Qt::DisplayRole) {
                    return account.comment();
                }
                break;
            case COLUMN_BALANCE:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(account.total().setScale(2, RoundingMode::HALF_UP).toString());
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                } else if (role == Qt::ForegroundRole) {
                    return account.total().signum() < 0 ? NEGATIVE_COLOR : POSITIVE_COLOR;
                }
                break;
            case COLUMN_WAITING:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(account.totalWaiting().setScale(2, RoundingMode::HALF_UP).toString());
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                } else if (role == Qt::ForegroundRole) {
                    return account.totalWaiting().signum() < 0 ? NEGATIVE_COLOR : POSITIVE_COLOR;
                }
                break;
        }

        return QVariant();
    };
};

AccountWindow::AccountWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::AccountWindow>()}, model_{make_unique<AccountFilterModel>()} {
    ui->setupUi(this);

    getMainWindow()->setupWindowMenu(ui->menuWindow);

    model_->setSourceModel(DataCache::cache().getAccountItemModel());
    ui->accountTableView->setModel(model_.get());

    auto header = ui->accountTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });

    Settings::loadWindowDimensions(this);
}

AccountWindow::~AccountWindow() {
}

void AccountWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
