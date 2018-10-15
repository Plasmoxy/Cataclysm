cmake_minimum_required(VERSION 3.12)
project(GLMTest)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories("include")
include_directories("C:/cmakelibs/glm")

add_executable(${PROJECT_NAME} ${SOURCES})