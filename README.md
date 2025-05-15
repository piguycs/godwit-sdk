# Godwit Game Development SDK 2025
This is a game development SDK/Framework that I will personally be using to make a mix of 2D and 3D games.

## Getting started

To build and run this project, you will need `meson`.

```shell
meson setup build
cd build
meson compile
# the example games bundled with this repo are under `./games/`
# lets run Game1
./games/game1/game1
```

## Core concepts
Still working on these as I go:
- Memory allocations are preferably done via an Arena allocator.
- Levels are initialised with on_load and on_update functions, sort of like Unity.

## Who is this for?
For me, but you can use it too :)

## What is this licensed under
All third party libraries and code retain their original license. Rest of the code is licensed under an Apache-2.0 license. All of the assets are CC0-1.0 unless explicitly specified.
