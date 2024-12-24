//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef PASSWORDTYPE_H
#define PASSWORDTYPE_H

namespace Settings {

enum class PasswordType {
    Unix,
    Pin,
    Short,
    Long,
};

}

#endif // PASSWORDTYPE_H
