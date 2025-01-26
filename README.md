# C++

[![License](docs/license.svg)](LICENSE)

Monorepo with C++ sources.

## Applications

+ [Password Generator](./apps/password_generator)
+ [Password Manager](./apps/password_manager)
+ [Sapper](./apps/sapper)

## Libraries

+ [pwdgen](./libs/pwdgen)
+ [common](./libs/common)
+ [qthelpers](./libs/qthelpers)

## Build

Requirements:
* gcc 10+ (C++20 compatible compiler)
* cmake 3.23+
* Qt6
* OpenSSL
* GTest

```sh
cmake . --preset <debug | release>
cmake --build --preset <debug | release> [--target <target>]
```

Application targets:
* password_generator
* password_manager
* sapper

## Test

1. Build all (no --target) for debug
2. Execute tests

```sh
ctest --preset debug
```
