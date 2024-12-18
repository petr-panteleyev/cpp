# C++

Monorepo with C++ sources.

## Build

```sh
cmake . --preset <Debug | Release>
cmake --build --preset <Debug | Release> [--target <target>]
```

Application targets:
* password_generator
* password_manager

## Test

1. Build all (no --target) for Debug
2. Execute tests

```sh
ctest --preset Debug
```


## Applications

+ [Password Generator](./apps/password_generator)
+ [Password Manager](./apps/password_manager)

## Libraries

+ [pwdgen](./libs/pwdgen)
