target_sources(password_manager PRIVATE
    cryptoexception.h
    aes256.h
    aes256.cpp
)
target_include_directories(password_manager PRIVATE .)
