#!/bin/sh

mkdir build
pushd build

src="../src/day1.c"

if [ "$1" = "--all" ]; then
    for file in ../src/*; do
	src=${src}$file
        echo "$file"
    done
fi

c_flags="-g3 -O0 -Wall -Wextra -Wconversion \
	 -Wdouble-promotion -Wno-unused-parameter \
	 -Wno-unused-function -Wno-sign-conversion \
	 -fsanitize=address -fsanitize=undefined -fsanitize-trap"

clang $c_flags $src -o target

popd
