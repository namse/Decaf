cmake_minimum_required(VERSION 3.14)

# SET( BINARY ${CMAKE_PROJECT_NAME} )
# SET( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sourceFiles
  "*.cpp"
)

add_library(
  ${CMAKE_PROJECT_NAME}Lib
  SHARED
  ${sourceFiles}
)

add_executable(
  ${CMAKE_PROJECT_NAME}Bin
  ${sourceFiles}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
