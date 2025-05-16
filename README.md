# Godwit Game Development SDK 2025
This is a game development SDK/Framework that I will personally be using to make a mix of 2D and 3D games.

## Getting started
This project uses C++11 along with Meson to compile everything. Clang is recommended.

### Dependencies
This project depends on `raylib` and `boost`. Be sure to have these libraries installed locally.

### Compiling on Linux
```shell
meson setup build
meson compile -C build
# lets run Game1
./build/games/game1/game1
```

### Compiling on Windows
(TODO: build and run this on a borrowed Windows laptop and publish build instructions)

## Additional info

## Core concepts
Still working on these as I go:
- Memory allocations are preferably done via an Arena allocator.
- Levels are initialised with on_load and on_update functions, sort of like Unity.

## What games are included
Just simple examples in the `./games/` folder.

## Who is this for?
For me, but you can use it too :)

## What is this licensed under
All third party libraries and code retain their original license. Rest of the code is licensed under an Apache-2.0 license. All of the assets are CC0-1.0 unless explicitly specified.
