//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "connectionprofiledialog.h"
#include "connectionprofile.h"
#include "connectionprofileitemmodel.h"
#include "connectionprofilemanager.h"
#include "databaseconnection.h"
#include "datasource.h"
#include "preparedstatement.h"
#include "resultset.h"
#include "sqlexception.h"
#include "ui_connectionprofiledialog.h"
#include <QSqlQuery>

using std::make_unique;

namespace {

int counter = 0;

std::unique_ptr<ConnectionProfile> buildProfile(const Ui::ConnectionProfileDialog &ui) {
    int port = ui.portEdit->text().toInt();
    return make_unique<ConnectionProfile>(ui.profileNameEdit->text(), ui.serverEdit->text(), port, ui.userEdit->text(),
                                          ui.passwordEdit->text(), ui.databaseEdit->text(), ui.schemaEdit->text());
}

} // namespace

ConnectionProfileDialog::ConnectionProfileDialog(QWidget *parent, ConnectionProfileManager *profileManager)
    : QDialog{parent}, ui{make_unique<Ui::ConnectionProfileDialog>()}, profileManager_{profileManager} {
    ui->setupUi(this);

    ui->portEdit->setValidator(new QIntValidator{1, 99999, this});

    ui->profileListView->setModel(profileManager_->getModel());

    auto selectionModel = ui->profileListView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::currentChanged, this,
            &ConnectionProfileDialog::onCurrentProfileChanged);

    connect(ui->closeButton, &QPushButton::clicked, [this]() { close(); });
    connect(ui->addButton, &QPushButton::clicked, this, &ConnectionProfileDialog::onNewButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &ConnectionProfileDialog::onSaveButton);
    connect(ui->testButton, &QPushButton::clicked, this, &ConnectionProfileDialog::onTestButton);
}

ConnectionProfileDialog::~ConnectionProfileDialog() {
}

void ConnectionProfileDialog::onNewButton() {
    profileManager_->getModel()->add(
        make_unique<ConnectionProfile>(QString("Profile%1").arg(++counter), "postgres", "money"));
}

void ConnectionProfileDialog::onDeleteButton() {
}

void ConnectionProfileDialog::onCurrentProfileChanged(const QModelIndex &current, const QModelIndex &previous) {
    if (!current.isValid()) {
        return;
    }
    const auto &p = profileManager_->getModel()->at(current.row());
    ui->profileNameEdit->setText(p.name());
    ui->serverEdit->setText(p.host());
    ui->portEdit->setText(QString::number(p.port()));
    ui->databaseEdit->setText(p.database());
    ui->userEdit->setText(p.user());
    ui->passwordEdit->setText(p.password());
    ui->databaseEdit->setText(p.database());
    ui->schemaEdit->setText(p.schema());

    ui->testResultLabel->setText("");
}

void ConnectionProfileDialog::onSaveButton() {
    auto index = ui->profileListView->currentIndex();
    if (!index.isValid()) {
        return;
    }

    profileManager_->getModel()->set(index, buildProfile(*ui.get()));
    profileManager_->setProfiles(ConnectionProfileManager::copy(profileManager_->getModel()->profiles()));
    profileManager_->saveProfiles();
}

void ConnectionProfileDialog::onTestButton() {
    auto index = ui->profileListView->currentIndex();
    if (!index.isValid()) {
        return;
    }

    auto profile = buildProfile(*ui.get());
    auto ds = profile->createDataSource();
    try {
        auto conn = ds->getConnection();
        auto st = conn->prepareStatement("SELECT 1");
        st->executeQuery();
        ui->testResultLabel->setText("Успех!");
    } catch (const SqlException &ex) {
        ui->testResultLabel->setText("Ошибка");
    }
}
