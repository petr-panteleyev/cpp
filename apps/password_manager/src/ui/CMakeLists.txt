# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(password_manager PRIVATE
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    cardtableitemmodel.h
    cardtableitemmodel.cpp
    cardtablesortfiltermodel.h
    cardtablesortfiltermodel.cpp
    fieldtableitemmodel.h
    fieldtableitemmodel.cpp
    fieldtablesortfiltermodel.h
    fieldtablesortfiltermodel.cpp
    cardeditdialog.h
    cardeditdialog.cpp
    cardeditdialog.ui
    editfieldlistmodel.h
    editfieldlistmodel.cpp
    translations.h
    translations.cpp
    fieldvalueeditdelegate.h
    fieldvalueeditdelegate.cpp
    newcarddialog.h
    newcarddialog.cpp
    newcarddialog.ui
    newnotedialog.h
    newnotedialog.cpp
    newnotedialog.ui
    passworddialog.h
    passworddialog.cpp
    passworddialog.ui
    changepassworddialog.h
    changepassworddialog.cpp
    changepassworddialog.ui
)
target_include_directories(password_manager PRIVATE .)
