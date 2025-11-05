#!/usr/bin/env bash

cd engine && clang-format -i $(find . -name '*.h' -o -name '*.cpp') -style=file && cd ..
