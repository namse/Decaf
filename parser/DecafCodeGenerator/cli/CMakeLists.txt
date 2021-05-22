cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
link_libraries(stdc++fs)

file(GLOB_RECURSE sourceFiles
  "*.cpp"
)

add_executable(
  ${CMAKE_PROJECT_NAME}Cli
  ${sourceFiles}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(${CMAKE_PROJECT_NAME}Cli ${CMAKE_PROJECT_NAME}Lib)
