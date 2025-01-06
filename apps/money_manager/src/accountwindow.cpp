//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "accountwindow.h"
#include "account.h"
#include "currency.h"
#include "datacache.h"
#include "decimal.h"
#include "globalcontext.h"
#include "qnamespace.h"
#include "ui_accountwindow.h"
#include <QSortFilterProxyModel>
#include <compare>
#include <unordered_map>

using Common::Decimal;
using Common::RoundingMode;
using GlobalContext::cache;
using std::make_unique;

namespace {

static const QColor NEGATIVE_COLOR{255, 0, 0};
static const QColor POSITIVE_COLOR{0, 128, 0};

static constexpr int COLUMN_NAME = 0;
static constexpr int COLUMN_CATEGORY = 1;
static constexpr int COLUMN_CURRENCY = 2;
static constexpr int COLUMN_INTEREST = 3;
static constexpr int COLUMN_CLOSING = 4;
static constexpr int COLUMN_COMMENT = 5;
static constexpr int COLUMN_BALANCE = 6;
static constexpr int COLUMN_WAITING = 7;

static std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_NAME, QHeaderView::ResizeToContents},     {COLUMN_CATEGORY, QHeaderView::ResizeToContents},
    {COLUMN_CURRENCY, QHeaderView::ResizeToContents}, {COLUMN_INTEREST, QHeaderView::ResizeToContents},
    {COLUMN_CLOSING, QHeaderView::ResizeToContents},  {COLUMN_COMMENT, QHeaderView::Stretch},
    {COLUMN_BALANCE, QHeaderView::ResizeToContents},  {COLUMN_WAITING, QHeaderView::ResizeToContents}};

} // namespace

class AccountWindow::AccountFilterModel : public QSortFilterProxyModel {
  public:
    explicit AccountFilterModel() {}
    ~AccountFilterModel(){};

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 8; };

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole) {
            return QVariant();
        }

        switch (section) {
            case COLUMN_NAME: return "Название";
            case COLUMN_CATEGORY: return "Категория";
            case COLUMN_CURRENCY: return "Валюта";
            case COLUMN_INTEREST: return "%%";
            case COLUMN_CLOSING: return "До";
            case COLUMN_COMMENT: return "Комментарий";
            case COLUMN_BALANCE: return "Баланс";
            case COLUMN_WAITING: return "Ожидает";
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid()) {
            return QVariant();
        }

        int row = mapToSource(index).row();
        auto account = cache().getAccount(row);

        switch (index.column()) {
            case COLUMN_NAME:
                if (role == Qt::DisplayRole) {
                    return account->name();
                }
                break;
            case COLUMN_CATEGORY:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(account->type().name());
                }
                break;
            case COLUMN_CURRENCY:
                if (role == Qt::DisplayRole) {
                    if (account->currencyUuid().has_value()) {
                        auto currency = cache().getCurrency(account->currencyUuid().value());
                        return currency.has_value() ? currency.value()->symbol() : "";
                    } else {
                        return "";
                    }
                }
                break;
            case COLUMN_INTEREST:
                if (role == Qt::DisplayRole) {
                    if (account->interest() <=> Decimal::ZERO == std::strong_ordering::equal) {
                        return "";
                    } else {
                        return QString::fromStdString(
                            account->interest().setScale(2, RoundingMode::HALF_UP).toString());
                    }
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                }
                break;
            case COLUMN_CLOSING:
                if (role == Qt::DisplayRole) {
                    return account->closingDate().has_value() ? account->closingDate().value().toString("dd.MM.yyyy")
                                                              : "";
                }
                break;
            case COLUMN_COMMENT:
                if (role == Qt::DisplayRole) {
                    return account->comment();
                }
                break;
            case COLUMN_BALANCE:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(account->total().setScale(2, RoundingMode::HALF_UP).toString());
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                } else if (role == Qt::ForegroundRole) {
                    return account->total().signum() < 0 ? NEGATIVE_COLOR : POSITIVE_COLOR;
                }
                break;
            case COLUMN_WAITING:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(
                        account->totalWaiting().setScale(2, RoundingMode::HALF_UP).toString());
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                } else if (role == Qt::ForegroundRole) {
                    return account->totalWaiting().signum() < 0 ? NEGATIVE_COLOR : POSITIVE_COLOR;
                }
                break;
        }

        return QVariant();
    };
};

AccountWindow::AccountWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::AccountWindow>()}, model_{make_unique<AccountFilterModel>()} {
    ui->setupUi(this);

    model_->setSourceModel(cache().getAccountItemModel());
    ui->accountTableView->setModel(model_.get());

    auto header = ui->accountTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });
}

AccountWindow::~AccountWindow() {
}
