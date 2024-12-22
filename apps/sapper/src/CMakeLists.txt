target_sources(sapper PRIVATE
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    buttoneventfilter.h
    buttoneventfilter.cpp
    picture.h
    picture.cpp
    gametimer.h
    gametimer.cpp
)

target_include_directories(sapper PRIVATE .)

add_subdirectory(game)
