//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <memory>
#include <vector>

class ConnectionProfile;
class ConnectionProfileItemModel;

class ConnectionProfileManager {
  public:
    ConnectionProfileManager();
    ~ConnectionProfileManager();

    void saveProfiles();
    void loadProfiles();

    void setProfiles(std::vector<std::unique_ptr<ConnectionProfile>> &&profiles);

    ConnectionProfileItemModel *getModel() const { return model_.get(); }

    int count() const noexcept { return profiles_.size(); }
    const ConnectionProfile &profile(int index) const { return *profiles_.at(index); }
    const std::vector<std::unique_ptr<ConnectionProfile>> &profiles() const noexcept { return profiles_; }

  public:
    static std::vector<std::unique_ptr<ConnectionProfile>>
    copy(const std::vector<std::unique_ptr<ConnectionProfile>> &profiles) noexcept;

  private:
    bool autoConnect_;

    std::vector<std::unique_ptr<ConnectionProfile>> profiles_;
    ConnectionProfile *defaultProfile_;

    std::unique_ptr<ConnectionProfileItemModel> model_;
};
