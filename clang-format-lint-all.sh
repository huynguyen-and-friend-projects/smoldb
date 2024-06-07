#!/bin/sh

find_cmd=`find './src' -name '*.c' -or -name '*.cpp*' -or -name '*.h' -or -name '*.h.in'`
find_cmd=$find_cmd `find './test' -name '*.c' -or -name '*.cpp*' -or -name '*.h' -or -name '*.h.in'`

for item in $find_cmd; do
  clang-tidy ${item}
  clang-format ${item} -i
done
