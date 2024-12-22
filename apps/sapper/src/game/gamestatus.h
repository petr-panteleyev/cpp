/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "enumclass.h"
#include <functional>

class GameStatus : public Common::EnumClass<GameStatus> {
  public:
    static const GameStatus INITIAL;
    static const GameStatus IN_PROGRESS;
    static const GameStatus SUCCESS;
    static const GameStatus FAILURE;

  public:
    bool isFinal() const noexcept { return isFinal_; }

  private:
    explicit GameStatus(const std::string &name, bool isFinal) noexcept : EnumClass{name}, isFinal_{isFinal} {}

  private:
    bool isFinal_;
};

using GameStatusRef = std::reference_wrapper<const GameStatus>;

inline const GameStatus GameStatus::INITIAL{"INITIAL", false};
inline const GameStatus GameStatus::IN_PROGRESS{"IN_PROGRESS", false};
inline const GameStatus GameStatus::SUCCESS{"SUCCESS", true};
inline const GameStatus GameStatus::FAILURE{"FAILURE", true};

template <>
inline const std::vector<GameStatusRef> Common::EnumClass<GameStatus>::values_{
    std::cref(GameStatus::INITIAL),
    std::cref(GameStatus::IN_PROGRESS),
    std::cref(GameStatus::SUCCESS),
    std::cref(GameStatus::FAILURE),
};

#endif // GAMESTATUS_H
