/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace Version {

#define str(s) #s
#define xstr(s) str(s)

#ifdef PROJECT_VERSION
static const std::string projectVersion{xstr(PROJECT_VERSION)};
#else
static const std::string projectVersion{"NOT DEFINED"};
#endif

} // namespace Version

#endif
