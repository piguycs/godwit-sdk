# Godwit Game Development SDK 2025
An ECS-driven game development SDK for C++17

## Getting started
This project uses C++17 along with Meson to compile everything.

### Dependencies
This project depends on `raylib`. The dependency is vendored using [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules). You do not need to have it installed locally for this project to compile.

### Compiling
```shell
meson setup build
meson compile -C build
```

### Running
The games will all be in the `build/games` directory.
```shell
$ ls build/games
simulation
$ ls build/games/simulation
simulation  simulation.p
$ # simulation is the binary and simulation.p is a directory with .o files
$ ./build/games/simulation/simulation
```

### An example of a 3D cellular automata simulation

`./build/games/simulation/simulation`

![CELLULAR AUTOMATA](https://cdn.lewd.host/ymICOiuS.png)

## Who is this for?
For me, but you can use it too :)

## What is this licensed under
All third party libraries and code retain their original license. Rest of the code is licensed under an Apache-2.0 license
