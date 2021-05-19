export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

cmake -S . -B .build

cmake --build .build

pushd .build

ctest

popd