#!/bin/sh

# an improvement over the old lint-all script, which lints the entire project.
# This one only lints the files staged, if they are valid source code files

# valid source code files include .c, .cxx, .cc, .cpp, .h, .hpp, .hh and .hxx
# preferably, use .c, .h, .cxx, .hxx only

# I use this for the pre-commit hook

# get names of all staged files
staged_files=($(git diff --name-only --cached))


for it in ${staged_files[@]}; do
    # remove longest substring before the dot, which is everything before the dot
    file_ext="${it##*.}"
    # format and lint C source files
    # either:
    # 1. there's only 1 character, c or h
    # 2. the starting character must be c or h, and the 2 following characters must be "pp" or "xx", and there should be no other characters
    # 3. matches exactly "cc"
    # Note: .in file not included
    grep_ext=$(echo $file_ext | grep -E "(^[ch](pp|xx)?$|^(cc|hh)$)")
    # $it is a source file, so $grep_ext is not empty
    if [ $grep_ext ]; then
        clang-format $it
        clang-tidy $it
        # clang-tidy complains
        if (($? != 0)); then
            clang_tidy_ret_code=1 # could be any number
        fi
    fi
    # format and lint CMake source files
    grep_ext=$(echo $it | grep -E "(^(CMakeLists.txt)$|.*\.(cmake)$)")
    if [ $grep_ext ]; then
        cmake-format $it 1>/dev/null
        cmake-lint $it
        if (( $? != 0 )); then
            cmake_lint_ret_code=1
        fi
    fi
    #format and lint Markdown files
    grep_ext=$(echo $it | grep -E "^(md)$")
    if [ $grep_ext ]; then
        vale $it
        markdownlint $it
        if (( $? != 0 )); then
            markdown_ret_code=1
        fi
    fi 
done

# if there's no error, $clang_tidy_ret_code would be empty since there's nothing named clang_tidy_ret_code, so [ $clang_tidy_ret_code ] is wrong
if [ $clang_tidy_ret_code ] || [ $cmake_lint_ret_code ] || [ $markdown_ret_code ]; then
    echo "Linter error, please fix :("
    exit 1
fi
