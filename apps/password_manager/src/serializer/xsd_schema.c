//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "xsd_schema.h"

static const uint8_t xsdSchemaBytes[] = {
#embed "../../resources/xsd/password-manager.xsd"
};

const struct xsd_schema_t XSD_SCHEMA = {.bytes_ = xsdSchemaBytes, .size_ = sizeof xsdSchemaBytes};
