target_sources(password_manager PRIVATE
    card.h
    card.cpp
    cardclass.h
    creditcardtype.h
    enums.cpp
    field.h
    field.cpp
    fieldtype.h
    picture.h
    picture.cpp
    recordtype.h
)
target_include_directories(password_manager PRIVATE .)
