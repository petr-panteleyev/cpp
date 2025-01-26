//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardwindow.h"
#include "account.h"
#include "card.h"
#include "category.h"
#include "datacache.h"
#include "imagecache.h"
#include "mainwindow.h"
#include "qnamespace.h"
#include "settings.h"
#include "ui_cardwindow.h"
#include <QSortFilterProxyModel>
#include <unordered_map>

using std::make_unique;

namespace {

constexpr int COLUMN_NUMBER = 0;
constexpr int COLUMN_CATEGORY = 1;
constexpr int COLUMN_ACCOUNT = 2;
constexpr int COLUMN_EXPIRATION = 3;
constexpr int COLUMN_COMMENT = 4;

constexpr int COLUMN_COUNT = COLUMN_COMMENT + 1;

std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_NUMBER, QHeaderView::ResizeToContents},  {COLUMN_CATEGORY, QHeaderView::ResizeToContents},
    {COLUMN_ACCOUNT, QHeaderView::ResizeToContents}, {COLUMN_EXPIRATION, QHeaderView::ResizeToContents},
    {COLUMN_COMMENT, QHeaderView::Stretch},
};

std::array<QString, COLUMN_COUNT> COLUMN_NAMES{"Номер", "Категория", "Счёт", "До", "Комментарий"};

} // namespace

class CardWindow::CardFilterModel final : public QSortFilterProxyModel {
  public:
    explicit CardFilterModel() {}
    ~CardFilterModel(){};

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
        auto card = DataCache::cache().getCard(row);

        auto account = DataCache::cache().getAccount(card->accountUuid());
        if (!account.has_value()) {
            return QVariant();
        }
        auto category = DataCache::cache().getCategory((*account)->categoryUuid());
        if (!category.has_value()) {
            return QVariant();
        }

        switch (index.column()) {
            case COLUMN_NUMBER:
                if (role == Qt::DisplayRole) {
                    return card->number();
                }
                break;
            case COLUMN_CATEGORY:
                if (role == Qt::DisplayRole) {
                    return (*category)->name();
                } else if (role == Qt::DecorationRole && (*category)->iconUuid().has_value()) {
                    auto image = ImageCache::getImage((*category)->iconUuid().value());
                    return QIcon(QPixmap::fromImage(*image.get()));
                }
                break;
            case COLUMN_ACCOUNT:
                if (role == Qt::DisplayRole) {
                    return (*account)->name();
                } else if (role == Qt::DecorationRole && (*account)->iconUuid().has_value()) {
                    auto image = ImageCache::getImage((*account)->iconUuid().value());
                    return QIcon(QPixmap::fromImage(*image.get()));
                }
                break;
            case COLUMN_EXPIRATION:
                if (role == Qt::DisplayRole) {
                    return card->expiration().toString("MM/yy");
                }
                break;
            case COLUMN_COMMENT:
                if (role == Qt::DisplayRole) {
                    return card->comment();
                }
                break;
        }

        return QVariant();
    }
};

CardWindow::CardWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::CardWindow>()}, model_{make_unique<CardFilterModel>()} {
    ui->setupUi(this);

    getMainWindow()->setupWindowMenu(ui->menuWindow);

    model_->setSourceModel(DataCache::cache().getCardItemModel());
    ui->cardTableView->setModel(model_.get());

    auto header = ui->cardTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });

    Settings::loadWindowDimensions(this);
}

CardWindow::~CardWindow() {
}

void CardWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
