export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

bash ./build.sh

pushd build

ctest

popd