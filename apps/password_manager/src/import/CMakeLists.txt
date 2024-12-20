target_sources(password_manager PRIVATE
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
