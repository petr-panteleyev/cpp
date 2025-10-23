# C++

[![License](https://www.panteleyev.org/badges/license-bsd-2.svg)](LICENSE)
![C++](https://www.panteleyev.org/badges/cpp-20.svg)

Монорепозиторий для C++.

## Приложения

+ [Password Generator](./apps/password_generator)
+ [Password Manager](./apps/password_manager)
+ [Sapper](./apps/sapper)

## Библиотеки

+ [pwdgen](./libs/pwdgen)
+ [common](./libs/common)
+ [qthelpers](./libs/qthelpers)

## Сборка

Требования:
* gcc 13+ (C++20 совместимый компилятор)
* cmake 3.31+
* Qt6.9
* OpenSSL
* Xerces-C++
* GTest

```sh
cmake . --preset <debug | release>
cmake --build --preset <debug | release> [--target <target>]
```

Цели для сборки приложений:
* password_generator
* password_manager
* sapper

## Тесты

1. Собрать все (no --target) в отладочном режиме
2. Запустить тесты

```sh
ctest --preset debug
```
