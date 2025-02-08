//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "connectionprofileitemmodel.h"
#include "connectionprofile.h"
#include "connectionprofilemanager.h"
#include "qnamespace.h"

ConnectionProfileItemModel::ConnectionProfileItemModel(ConnectionProfileManager *profileManager)
    : QAbstractItemModel{nullptr} {

    const auto &existing = profileManager->profiles();
    profiles_.reserve(existing.size());
    for (const auto &p : existing) {
        profiles_.push_back(std::unique_ptr<ConnectionProfile>(new ConnectionProfile{*p.get()}));
    }
}

ConnectionProfileItemModel::~ConnectionProfileItemModel() {
}

void ConnectionProfileItemModel::setProfiles(std::vector<std::unique_ptr<ConnectionProfile>> &&profiles) {
    beginResetModel();
    profiles_ = std::move(profiles);
    endResetModel();
}

void ConnectionProfileItemModel::add(std::unique_ptr<ConnectionProfile> &&profile) {
    beginInsertRows(QModelIndex(), profiles_.size(), profiles_.size());
    profiles_.push_back(std::move(profile));
    endInsertRows();
}

void ConnectionProfileItemModel::set(const QModelIndex &index, std::unique_ptr<ConnectionProfile> &&profile) {
    profiles_[index.row()] = std::move(profile);
    emit dataChanged(index, index);
}

QVariant ConnectionProfileItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    return profiles_.at(index.row())->name();
}
