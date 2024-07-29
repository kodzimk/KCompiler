cmake_minimum_required(VERSION 3.29)

project(KCompiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(compiler KCompiler/src/main.cpp)
target_include_directories(Engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Kcompiler/src")