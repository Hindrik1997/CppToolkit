cmake_minimum_required(VERSION 3.12)
project(CppToolkit)

set(CMAKE_CXX_STANDARD 11)

add_library(CppToolkit cpp_tools.h src/delayed_init.h demo/demo.cpp)