#!/bin/sh

for item in `find . -not -path './build/*' -name '*.c' -or -name '*.h' -or -name '*.h.in'`; do
  clang-tidy ${item}
  clang-format ${item} -i
done
