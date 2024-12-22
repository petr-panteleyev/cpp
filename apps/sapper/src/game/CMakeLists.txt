target_sources(sapper PRIVATE
    boardsize.h
    gamestatus.h
    game.h
    game.cpp
    board.h
    board.cpp
    callbacks.h
)

target_include_directories(sapper PRIVATE .)
