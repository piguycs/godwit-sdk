#!/usr/bin/env bash

cd engine && clang-format -i $(find . -name '*.h' -o -name '*.cpp') -style=file && cd ..

# I decided to use .hpp files for the game code, just to see which one I like better
cd games/simulation && clang-format -i $(find . -name '*.hpp' -o -name '*.cpp') -style=file && cd ../..
