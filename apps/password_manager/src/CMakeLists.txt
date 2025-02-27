# Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(password_manager PRIVATE
    main.cpp
    serializer.h
    serializer.cpp
    exceptions.h
    str.h
)
target_include_directories(password_manager PRIVATE .)

add_subdirectory(crypto)
add_subdirectory(model)
add_subdirectory(ui)
add_subdirectory(import)
add_subdirectory(settings)
