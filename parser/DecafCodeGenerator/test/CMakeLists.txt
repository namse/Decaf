cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

enable_testing()

add_executable(
  ${CMAKE_PROJECT_NAME}Test
  ${TEST_SOURCES}
)
target_link_libraries(
  ${CMAKE_PROJECT_NAME}Test
  PUBLIC
  gtest_main
  ${CMAKE_PROJECT_NAME}Lib
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}Test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
