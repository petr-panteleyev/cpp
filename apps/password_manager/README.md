# Password Manager

**WORK IN PROGRESS**

Desktop application to store passwords, credit card numbers and other sensitive information. Application uses 256-bit AES encryption.

![Screenshot](docs/main-window.png)

## Security Considerations

Application enforces security via file encryption only. Application makes no effort to counter-attacks targeted to user account, operating system or hardware including RAM.

## Build

Requirements:
* Qt6
* OpenSSL

**Debug**


```sh
cmake . --preset Debug
cmake --build --preset Debug
```

**Release**


```sh
cmake . --preset Release
cmake --build --preset Release
```
