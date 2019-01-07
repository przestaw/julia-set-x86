cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME Julia_x86-64)

set(CMAKE_PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE RELASE)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)
enable_language(ASM_NASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# ADD SOURCE FILES
set(SOURCE_FILES src/main.cpp src/gen_Julia.asm src/Raw_Julia.cpp include/Raw_Julia.h)

find_package(PkgConfig REQUIRED)
pkg_search_module(SFML REQUIRED sfml-all)

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} sfml-audio sfml-graphics sfml-window sfml-system)