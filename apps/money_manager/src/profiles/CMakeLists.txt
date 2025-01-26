# Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    connectdialog.h
    connectdialog.cpp
    connectdialog.ui
    connectionprofile.h
    connectionprofile.cpp
    connectionprofiledialog.h
    connectionprofiledialog.cpp
    connectionprofiledialog.ui
    connectionprofileitemmodel.h
    connectionprofileitemmodel.cpp
    connectionprofilemanager.h
    connectionprofilemanager.cpp
)

target_include_directories(money_manager PRIVATE .)
