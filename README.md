# Godwit Game Development SDK 2025
This is a game development SDK/Framework that I will personally be using to make a mix of 2D and 3D games.

## Getting started
This project uses C++17 along with Meson to compile everything.

If you want to just test out the games, pre-built binaries are available via our CI/CD pipeline. You can download the latest binaries from [nightly.link](https://nightly.link/piguycs/godwit-sdk/workflows/build/main).

### Dependencies
This project depends on `raylib`. The dependency is vendored using [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules). You do not need to have it installed locally for this project to compile.

### Compiling
```shell
meson setup build
meson compile -C build
```

### Running

The games will all be in the `build/Games` directory.
```shell
$ ls build/Games
game1
$ # game1 is the directory containing the binary for Games/game1
$ ls build/Games/game1
game1  game1.p
$ # game1 is the binary and game1.p is a directory with .o files
$ ./build/Games/game1/game1
```

## Additional info

## Core concepts
Still working on these as I go:
- Memory allocations are preferably done via an Arena allocator.
- Levels are initialised with on_load and on_update functions, sort of like Unity.

## What games are included
Just simple examples in the `./Games/` folder.

## Who is this for?
For me, but you can use it too :)

## What is this licensed under
All third party libraries and code retain their original license. Rest of the code is licensed under an Apache-2.0 license. All of the assets are CC0-1.0 unless explicitly specified.
