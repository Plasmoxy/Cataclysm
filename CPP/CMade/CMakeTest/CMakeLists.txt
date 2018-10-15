cmake_minimum_required(VERSION 3.12)
project(CMakeTest)

include_directories("src/somelib")
add_executable(hello src/hello.cpp src/somelib/lib.cpp)