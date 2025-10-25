//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QAbstractItemModel>

class ConnectionProfile;
class ConnectionProfileManager;

class ConnectionProfileItemModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    explicit ConnectionProfileItemModel(ConnectionProfileManager *profileManager);
    ~ConnectionProfileItemModel();

    const ConnectionProfile &at(int row) const { return *profiles_.at(row); }
    void add(std::unique_ptr<ConnectionProfile> &&profile);
    void set(const QModelIndex &index, std::unique_ptr<ConnectionProfile> &&profile);
    const std::vector<std::unique_ptr<ConnectionProfile>> &profiles() const noexcept { return profiles_; }
    void setProfiles(std::vector<std::unique_ptr<ConnectionProfile>> &&profiles);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return QModelIndex(); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return profiles_.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 1; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  private:
    std::vector<std::unique_ptr<ConnectionProfile>> profiles_;
};
