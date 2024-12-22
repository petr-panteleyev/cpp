/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "gamestatus.h"

class GameCallbackHandler {
  public:
    virtual void onCellChanged(int x, int newValue) = 0;
    virtual void onGameStatusChanged(int x, const GameStatus &newStatus) = 0;
};

#endif // CALLBACKS_H
