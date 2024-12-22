# Sapper Game

Yet another Sapper game.

![Big Board](docs/board_big.png)

## Board Sizes

Three standard board sizes:
* 8 x 8, 10 mines
* 16 x 16, 40 mines
* 30 x 16, 99 mines

## Build

Requirements:
* Qt6

**Debug**

```sh
cmake . --preset Debug
cmake --build --preset Debug --target sapper
```

**Release**

```sh
cmake . --preset Release
cmake --build --preset Release --target sapper
```
