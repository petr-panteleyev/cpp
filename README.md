# C++

[![License](docs/license.svg)](LICENSE)

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
* gcc 10+ (C++20 совместимый компилятор)
* cmake 3.23+
* Qt6
* OpenSSL
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
