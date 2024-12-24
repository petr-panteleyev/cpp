# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(password_manager PRIVATE
    importaction.h
    importrecord.h
    importutil.h
    importutil.cpp
    importdialog.h
    importdialog.cpp
    importdialog.ui
    importrecordtablemodel.h
    importrecordtablemodel.cpp
)
target_include_directories(password_manager PRIVATE .)
