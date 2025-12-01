mkdir build
pushd build

c_flags="-g3 -O0 -Wall -Wextra -Wconversion \
	 -Wdouble-promotion -Wno-unused-parameter \
	 -Wno-unused-function -Wno-sign-conversion \
	 -fsanitize=address -fsanitize=undefined -fsanitize-trap"

src="../src/day1.c"

clang $c_flags $src -o target

popd
