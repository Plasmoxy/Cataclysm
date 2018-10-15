cmake_minimum_required(VERSION 3.12)
project(CMakeTest)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories("include")
add_executable(hello ${SOURCES})