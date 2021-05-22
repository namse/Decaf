cmake_minimum_required(VERSION 3.14)
project(Decaf C CXX)

SET(CMAKE_CXX_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cli)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
