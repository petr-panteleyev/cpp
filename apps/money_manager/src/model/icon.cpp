//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "icon.h"

Icon::Icon(QUuid uuid, const QString &name, const QByteArray &bytes, long created, long modified)
    : MoneyRecord(uuid, created, modified), name_{name}, bytes_{bytes} {
}
