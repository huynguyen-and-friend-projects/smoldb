#!/bin/sh

find_cmd=`find './src' -name '*.c' -or -name '*.cpp*' -or -name '*.h' -or -name '*.h.in'`
find_cmd=$find_cmd `find './test' -name '*.c' -or -name '*.cpp*' -or -name '*.h' -or -name '*.h.in'`

for item in $find_cmd; do
  clang-format ${item} -i
  clang-tidy ${item}
  if (( $? != 0 )); then
      clang_tidy_ret_code=1
  fi
done

if [ $clang_tidy_ret_code ]; then
    echo $clang_tidy_ret_code
    echo "Linter error"
    exit 1
fi
