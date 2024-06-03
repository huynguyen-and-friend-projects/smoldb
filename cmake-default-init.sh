#!/bin/bash

rm -rf ./build compile_commands.json
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -G Ninja -DCMAKE_C_COMPILER=clang ..
cd ..
ln -s ./build/compile_commands.json compile_commands.json