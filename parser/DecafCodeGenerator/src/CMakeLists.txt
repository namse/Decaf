cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
find_package(Threads)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sourceFiles
  "*.cpp"
)

add_library(
  ${CMAKE_PROJECT_NAME}Lib
  SHARED
  ${sourceFiles}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(${CMAKE_PROJECT_NAME}Lib ${llvm_libs})