# C++

[![License](https://www.panteleyev.org/badges/license-bsd-2.svg)](LICENSE)
![C++](https://www.panteleyev.org/badges/cpp-20.svg)

Monorepo for C++ exercises.

## Applications

+ [Password Generator](./apps/password_generator)
+ [Password Manager](./apps/password_manager)
+ [Sapper](./apps/sapper)

## Libraries

+ [common](./libs/common)
+ [cryptography](./libs/cryptography)
+ [pwdgen](./libs/pwdgen)
+ [qthelpers](./libs/qthelpers)

## Build Environment

This project is built using the following environment:
* gcc 15.2.0
* cmake 4.1.2
* Qt6.9.2
* libcrypto 3.3.3
* libxerces-c 3.2.5
* GTest 1.13.0

```sh
cmake . --preset <debug | release>
cmake --build --preset <debug | release> [--target <target>]
```

Build targets:
* password_generator
* password_manager
* sapper

## Tests

```sh
cmake --build --preset <debug | release>
ctest --preset <debug | release>
```

or


```sh
cmake --workflow --preset <debug | release>
```

## More

[Some notes on C++20 modules experience](docs/modules.md)
