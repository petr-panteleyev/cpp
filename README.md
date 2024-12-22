# C++

[![License](docs/license.svg)](LICENSE)

Monorepo with C++ sources.

## Build

Requirements:
* gcc 10+ (C++20 compatible compiler)
* cmake 3.23+
* Qt6
* OpenSSL
* GTest

```sh
cmake . --preset <Debug | Release>
cmake --build --preset <Debug | Release> [--target <target>]
```

Application targets:
* password_generator
* password_manager
* sapper

## Test

1. Build all (no --target) for Debug
2. Execute tests

```sh
ctest --preset Debug
```


## Applications

+ [Password Generator](./apps/password_generator)
+ [Password Manager](./apps/password_manager)
+ [Sapper](./apps/sapper)

## Libraries

+ [pwdgen](./libs/pwdgen)
