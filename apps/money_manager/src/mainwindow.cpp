//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.h"
#include "account.h"
#include "accountwindow.h"
#include "categorytype.h"
#include "categorywindow.h"
#include "connectdialog.h"
#include "connectionprofile.h"
#include "connectionprofiledialog.h"
#include "connectionprofilemanager.h"
#include "contact.h"
#include "contactwindow.h"
#include "currencywindow.h"
#include "databaseconnection.h"
#include "datacache.h"
#include "datasource.h"
#include "decimal.h"
#include "globalcontext.h"
#include "moneydao.h"
#include "qnamespace.h"
#include "qsortfilterproxymodel.h"
#include "qthelpers.h"
#include "sqlexception.h"
#include "transaction.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSortFilterProxyModel>

using GlobalContext::cache;
using GlobalContext::dao;
using std::make_unique;

namespace {

constexpr int COLUMN_DAY = 0;
constexpr int COLUMN_TYPE = 1;
constexpr int COLUMN_DEBIT_ACCOUNT = 2;
constexpr int COLUMN_CREDIT_ACCOUNT = 3;
constexpr int COLUMN_COUNTERPARTY = 4;
constexpr int COLUMN_COMMENT = 5;
constexpr int COLUMN_AMOUNT = 6;
constexpr int COLUMN_ATTACHMENTS = 7;

const QColor COLOR_DEBIT{255, 0, 0};
const QColor COLOR_CREDIT{0, 128, 0};
const QColor COLOR_TRANSFER{0, 0, 255};

static std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_DAY, QHeaderView::ResizeToContents},           {COLUMN_TYPE, QHeaderView::ResizeToContents},
    {COLUMN_DEBIT_ACCOUNT, QHeaderView::ResizeToContents}, {COLUMN_CREDIT_ACCOUNT, QHeaderView::ResizeToContents},
    {COLUMN_COUNTERPARTY, QHeaderView::ResizeToContents},  {COLUMN_COMMENT, QHeaderView::Stretch},
    {COLUMN_AMOUNT, QHeaderView::ResizeToContents},        {COLUMN_ATTACHMENTS, QHeaderView::ResizeToContents}};

static const std::array<QString, 12> MONTHS{"Январь", "Февраль", "Март",     "Апрель",  "Май",    "Июнь",
                                            "Июль",   "Август",  "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};

void enableActionsOnConnect(Ui::MainWindow *ui, bool connected) {
    QtHelpers::enableActions(connected, {ui->actionAccountWindow, ui->actionCategoryWindow, ui->actionContactWindow,
                                         ui->actionCurrencyWindow, ui->actionCurrentMonth, ui->actionNextMonth,
                                         ui->actionPrevMonth});
}

void showWindow(QWidget *w) {
    w->show();
    w->activateWindow();
    w->raise();
}

void setDate(const std::unique_ptr<Ui::MainWindow> &ui, const QDate &date) {
    ui->monthComboBox->setCurrentIndex(date.month() - 1);
    ui->yearSpinner->setValue(date.year());
}

} // namespace

class MainWindow::TransactionFilterModel final : public QSortFilterProxyModel {
  public:
    explicit TransactionFilterModel() : date_{QDate::currentDate()} {}
    ~TransactionFilterModel(){};

    QDate date() const noexcept { return date_; }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 8; };

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole) {
            return QVariant();
        }

        switch (section) {
            case COLUMN_DAY: return "День";
            case COLUMN_TYPE: return "Тип";
            case COLUMN_DEBIT_ACCOUNT: return "Исходный счёт";
            case COLUMN_CREDIT_ACCOUNT: return "Счёт получателя";
            case COLUMN_COUNTERPARTY: return "Контрагент";
            case COLUMN_COMMENT: return "Комментарий";
            case COLUMN_AMOUNT: return "Сумма";
            case COLUMN_ATTACHMENTS: return "";
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid()) {
            return QVariant();
        }

        int row = mapToSource(index).row();
        auto tr = cache().getTransaction(row);

        switch (index.column()) {
            case COLUMN_DAY:
                if (role == Qt::DisplayRole) {
                    return tr->transactionDate().toString("dd");
                }
                break;
            case COLUMN_TYPE:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(tr->type().name());
                }
                break;
            case COLUMN_DEBIT_ACCOUNT:
                if (role == Qt::DisplayRole) {
                    auto acc = cache().getAccount(tr->accountDebitedUuid());
                    return acc.has_value() ? acc.value()->name() : "";
                }
                break;
            case COLUMN_CREDIT_ACCOUNT:
                if (role == Qt::DisplayRole) {
                    auto acc = cache().getAccount(tr->accountCreditedUuid());
                    return acc.has_value() ? acc.value()->name() : "";
                }
                break;
            case COLUMN_COUNTERPARTY:
                if (role == Qt::DisplayRole) {
                    auto contact = cache().getContact(tr->contactUuid().value_or(QUuid()));
                    return contact.has_value() ? contact.value()->name() : "";
                }
                break;
            case COLUMN_COMMENT:
                if (role == Qt::DisplayRole) {
                    return tr->comment();
                }
                break;
            case COLUMN_AMOUNT:
                if (role == Qt::DisplayRole) {
                    return QString::fromStdString(tr->amount().setScale(2, Common::RoundingMode::HALF_UP).toString());
                } else if (role == Qt::TextAlignmentRole) {
                    return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
                } else if (role == Qt::ForegroundRole) {
                    if (tr->accountCreditedType() == CategoryType::EXPENSES) {
                        return COLOR_DEBIT;
                    } else if (tr->accountCreditedType() == tr->accountDebitedType()) {
                        return COLOR_TRANSFER;
                    } else {
                        return COLOR_CREDIT;
                    }
                }
                break;
        }
        return QVariant();
    }

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        auto leftTr = cache().getTransaction(left.row());
        auto rightTr = cache().getTransaction(right.row());

        if (leftTr->transactionDate() == rightTr->transactionDate()) {
            return leftTr->created() < rightTr->created();
        } else {
            return leftTr->transactionDate() < rightTr->transactionDate();
        }
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        auto trDate = cache().getTransaction(sourceRow)->transactionDate();
        return trDate.month() == date_.month() && trDate.year() == date_.year();
    }

    void setDate(QDate date) {
        date_ = date;
        invalidateFilter();
    }

    void previousMonth() {
        date_ = date_.addMonths(-1);
        invalidateFilter();
    }

    void nextMonth() {
        date_ = date_.addMonths(1);
        invalidateFilter();
    }

  private:
    QDate date_;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::MainWindow>()}, connected_{false},
      profileManager_{make_unique<ConnectionProfileManager>()},
      connectionProfileDialog_{new ConnectionProfileDialog{this, profileManager_.get()}},
      connectDialog_{new ConnectDialog(this, profileManager_.get())}, accountWindow_{new AccountWindow{this}},
      categoryWindow_{new CategoryWindow{this}}, contactWindow_{new ContactWindow{this}},
      currencyWindow_{new CurrencyWindow{this}}, model_{make_unique<MainWindow::TransactionFilterModel>()} {
    ui->setupUi(this);

    profileManager_->loadProfiles();

    model_->setSourceModel(cache().getTransactionItemModel());
    ui->transactionTableView->setModel(model_.get());

    model_->sort(COLUMN_DAY, Qt::DescendingOrder);

    auto header = ui->transactionTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    for (auto month : MONTHS) {
        ui->monthComboBox->addItem(month);
    }

    setDate(ui, QDate::currentDate());

    connected_.subscribe([this](auto &, auto &value) { enableActionsOnConnect(ui.get(), value); });

    connect(ui->actionConnect, &QAction::triggered, [this]() { connectDialog_->show(); });
    connect(ui->actionExit, &QAction::triggered, [this]() { close(); });
    connect(ui->actionProfiles, &QAction::triggered, [this]() { connectionProfileDialog_->show(); });

    connect(ui->actionCurrentMonth, &QAction::triggered, [this]() {
        model_->setDate(QDate::currentDate());
        setDate(ui, model_->date());
    });
    connect(ui->actionNextMonth, &QAction::triggered, [this]() {
        model_->nextMonth();
        setDate(ui, model_->date());
    });
    connect(ui->actionPrevMonth, &QAction::triggered, [this]() {
        model_->previousMonth();
        setDate(ui, model_->date());
    });

    connect(ui->monthComboBox, &QComboBox::currentIndexChanged, [this](auto index) {
        auto date = model_->date();
        date.setDate(date.year(), index + 1, date.day());
        model_->setDate(date);
    });
    connect(ui->yearSpinner, &QSpinBox::valueChanged, [this](auto year) {
        auto date = model_->date();
        date.setDate(year, date.month(), date.day());
        model_->setDate(date);
    });

    // windows
    connect(ui->actionAccountWindow, &QAction::triggered, [this]() { showWindow(accountWindow_); });
    connect(ui->actionCategoryWindow, &QAction::triggered, [this]() { showWindow(categoryWindow_); });
    connect(ui->actionContactWindow, &QAction::triggered, [this]() { showWindow(contactWindow_); });
    connect(ui->actionCurrencyWindow, &QAction::triggered, [this]() { showWindow(currencyWindow_); });

    // dialogs
    connect(connectDialog_, &QDialog::accepted, this, &MainWindow::onConnect);
}

MainWindow::~MainWindow() {
}

void MainWindow::onConnect() {
    try {
        auto profile = connectDialog_->profile();
        auto ds = profile->createDataSource();
        dao().initialize(ds);
        dao().preload();
        connected_ = true;
    } catch (const SqlException &ex) {
        QMessageBox::critical(this, "SQL Exception", ex.what());
    }
}
