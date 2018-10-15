cmake_minimum_required(VERSION 3.12)
project(GLMTest)

file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(glm REQUIRED)

include_directories("include")
add_executable($PROJECT_NAME $SOURCES)

target_link_libraries($PROJECT_NAME glm)