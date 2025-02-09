//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "connectionprofilemanager.h"
#include "connectionprofile.h"
#include "connectionprofileitemmodel.h"
#include <QSettings>
#include <memory>

namespace {

const QString PROFILES_ARRAY{"profiles"};
const QString NAME{"name"};
const QString HOST{"host"};
const QString PORT{"port"};
const QString USER{"user"};
const QString PASSWORD{"password"};
const QString DATABASE{"database"};
const QString SCHEMA{"schema"};

} // namespace

ConnectionProfileManager::ConnectionProfileManager()
    : defaultProfile_{nullptr}, model_{std::make_unique<ConnectionProfileItemModel>(this)} {
}

ConnectionProfileManager::~ConnectionProfileManager() {
}

void ConnectionProfileManager::saveProfiles() {
    QSettings settings;

    settings.beginWriteArray(PROFILES_ARRAY, profiles_.size());

    auto index = 0;
    for (const auto &p : profiles_) {
        settings.setArrayIndex(index++);
        settings.setValue(NAME, p->name());
        settings.setValue(HOST, p->host());
        settings.setValue(PORT, p->port());
        settings.setValue(USER, p->user());
        settings.setValue(PASSWORD, p->password());
        settings.setValue(DATABASE, p->database());
        settings.setValue(SCHEMA, p->schema());
    }
    settings.endArray();
}

void ConnectionProfileManager::loadProfiles() {
    QSettings settings;
    profiles_.clear();
    auto size = settings.beginReadArray(PROFILES_ARRAY);
    for (auto i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        profiles_.push_back(std::make_unique<ConnectionProfile>(
            settings.value(NAME).toString(), settings.value(HOST).toString(), settings.value(PORT).toInt(),
            settings.value(USER).toString(), settings.value(PASSWORD).toString(), settings.value(DATABASE).toString(),
            settings.value(SCHEMA).toString()));
    }
    settings.endArray();
    model_->setProfiles(copy(profiles_));
}

void ConnectionProfileManager::setProfiles(std::vector<std::unique_ptr<ConnectionProfile>> &&profiles) {
    profiles_ = std::move(profiles);
}

std::vector<std::unique_ptr<ConnectionProfile>>
ConnectionProfileManager::copy(const std::vector<std::unique_ptr<ConnectionProfile>> &profiles) noexcept {
    std::vector<std::unique_ptr<ConnectionProfile>> copy;
    copy.reserve(profiles.size());
    for (const auto &p : profiles) {
        copy.push_back(std::unique_ptr<ConnectionProfile>(new ConnectionProfile(*p.get())));
    }
    return copy;
}
