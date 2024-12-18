add_library(pwdgen STATIC)

target_compile_options(pwdgen PRIVATE
    -Werror
    -Wall
    -Wpedantic
)

target_sources(pwdgen
    PUBLIC
        generator.h
    PRIVATE
        characterset.h
        characterset.cpp
        generator.cpp
)

install(TARGETS pwdgen
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
