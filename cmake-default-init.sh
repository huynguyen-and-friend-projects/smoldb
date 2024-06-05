#!/bin/bash

# run this every time you change one of the CMakeLists
rm -rf ./build compile_commands.json
mkdir build
cd build
# default: compile with clang a release version using ninja.build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -G Ninja -DCMAKE_C_COMPILER=clang ..
cd ..
ln -s ./build/compile_commands.json compile_commands.json

help_msg="
what's next?

build the executable:
  cmake --build build
get the executable onto the project root:
  cmake --install build
"

echo "$help_msg"
