cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

link_libraries(stdc++fs)

find_package(Threads)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB_RECURSE sourceFiles
  "*.cpp"
)

add_executable(
  ${CMAKE_PROJECT_NAME}Cli
  ${sourceFiles}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

llvm_map_components_to_libnames(llvm_libs
  support
  core
  irreader
  target

  # CodeGen
  aarch64codegen
  amdgpucodegen
  armcodegen
  avrcodegen
  bpfcodegen
  codegen
  hexagoncodegen
  lanaicodegen
  mipscodegen
  msp430codegen
  nativecodegen
  nvptxcodegen
  powerpccodegen
  riscvcodegen
  sparccodegen
  systemzcodegen
  webassemblycodegen
  x86codegen
  xcorecodegen

  # Asm Parser
  aarch64asmparser
  amdgpuasmparser
  armasmparser
  asmparser
  avrasmparser
  bpfasmparser
  hexagonasmparser
  lanaiasmparser
  mipsasmparser
  msp430asmparser
  powerpcasmparser
  riscvasmparser
  sparcasmparser
  systemzasmparser
  webassemblyasmparser
  x86asmparser
)
#  llvm-config --components

target_link_libraries(${CMAKE_PROJECT_NAME}Cli PUBLIC ${CMAKE_PROJECT_NAME}Lib)
target_link_libraries(${CMAKE_PROJECT_NAME}Cli PRIVATE ${llvm_libs})