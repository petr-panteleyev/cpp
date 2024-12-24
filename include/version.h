//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace Version {

#define version_str(s) #s
#define version_xstr(s) version_str(s)

#ifdef PROJECT_VERSION
static const std::string projectVersion{version_xstr(PROJECT_VERSION)};
#else
static const std::string projectVersion{"NOT DEFINED"};
#endif

#ifdef BUILD_TIMESTAMP
static const std::string buildDate{version_xstr(BUILD_TIMESTAMP)};
#else
static const std::string buildDate{"NOT DEFINED"};
#endif

} // namespace Version

#endif
