# C++

[![License](https://www.panteleyev.org/badges/license-bsd-2.svg)](LICENSE)
![C++](https://www.panteleyev.org/badges/cpp-23.svg)

Монорепозиторий для C++.

## Приложения

+ [Password Generator](./apps/password_generator)
+ [Password Manager](./apps/password_manager)
+ [Sapper](./apps/sapper)
+ [Money Manager](./apps/money_manager)

## Библиотеки

+ [common](./libs/common)
+ [cryptography](./libs/cryptography)
+ [pwdgen](./libs/pwdgen)
+ [qthelpers](./libs/qthelpers)

## Сборка

Проект собирается на следующем окружении:
* Alt Linux p11
* GCC 15.2.0
* CMake 4.1.2
* Qt 6.9.2
* libcrypto 3.3.3
* libxerces-c 3.2.5
* GTest 1.13.0

```sh
cmake . --preset <debug | release>
cmake --build --preset <debug | release> [--target <target>]
```

Цели для сборки приложений:
* password_generator
* password_manager
* sapper
* money_manager

## Тесты

```sh
cmake --build --preset <debug | release>
ctest --preset <debug | release>
```

или


```sh
cmake --workflow --preset <debug | release>
```


## Сторонние исходные тексты

Временно включены в репозиторий до появления в репозиториях Alt Linux:
+ [Boost.Decimal](https://develop.decimal.cpp.al/decimal/overview.html)


## Разное

[Заметки по опыту использования модулей C++20](docs/modules.md)
