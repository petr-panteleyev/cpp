//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <stdint.h>

#ifdef __cplusplus
namespace xsd {
extern "C" {
#endif

struct xsd_schema_t {
    const uint8_t *bytes_;
    unsigned long size_;
};

extern const struct xsd_schema_t XSD_SCHEMA;

#ifdef __cplusplus
}
}
#endif
