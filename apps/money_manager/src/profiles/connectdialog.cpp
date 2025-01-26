//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "connectdialog.h"
#include "connectionprofileitemmodel.h"
#include "connectionprofilemanager.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent, ConnectionProfileManager *profileManager)
    : QDialog{parent}, ui{std::make_unique<Ui::ConnectDialog>()}, profileManager_{profileManager} {
    ui->setupUi(this);

    ui->profilesComboBox->setModel(profileManager->getModel());
}

ConnectDialog::~ConnectDialog() {
}

std::shared_ptr<ConnectionProfile> ConnectDialog::profile() const {
    auto index = ui->profilesComboBox->currentIndex();
    return profileManager_->profile(index);
}
