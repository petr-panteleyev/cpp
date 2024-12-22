# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(password_manager PRIVATE
    settings.h
    settings.cpp
    settingsdialog.h
    settingsdialog.cpp
    settingsdialog.ui
)

target_include_directories(password_manager PRIVATE .)
