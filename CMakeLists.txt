cmake_minimum_required(VERSION 3.6)
project(AnalisadorSintatico)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(AnalisadorSintatico ${SOURCE_FILES})