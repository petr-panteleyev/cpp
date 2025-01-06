//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONNECTIONPROFILEITEMMODEL_H
#define CONNECTIONPROFILEITEMMODEL_H

#include <QAbstractItemModel>

class ConnectionProfile;
class ConnectionProfileManager;

class ConnectionProfileItemModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    explicit ConnectionProfileItemModel(ConnectionProfileManager *profileManager);
    ~ConnectionProfileItemModel();

    const std::shared_ptr<ConnectionProfile> &at(int row) const { return profiles_.at(row); }
    void add(const std::shared_ptr<ConnectionProfile> &profile);
    void set(const QModelIndex &index, const std::shared_ptr<ConnectionProfile> &profile);
    const std::vector<std::shared_ptr<ConnectionProfile>> &profiles() const noexcept { return profiles_; }
    void setProfiles(const std::vector<std::shared_ptr<ConnectionProfile>> &profiles);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        return createIndex(row, column);
    }
    QModelIndex parent(const QModelIndex &index) const override { return QModelIndex(); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return profiles_.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 1; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  private:
    std::vector<std::shared_ptr<ConnectionProfile>> profiles_;
};

#endif // CONNECTIONPROFILEITEMMODEL_H
