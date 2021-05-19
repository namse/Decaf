# CC=clang-9 CXX=clang++-9 bazel test --config=clang_config --test_output=all //:test --verbose_failures

export CC=/usr/bin/clang-9
export CXX=/usr/bin/clang++-9

cmake -S . -B build

cmake --build build

pushd build

ctest

popd