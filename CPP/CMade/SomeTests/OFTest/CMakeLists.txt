cmake_minimum_required(VERSION 3.12)
project(OFTest)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_LIST OF_LIBS_INCLUDES "C:/of/libs/*")

message("${OF_LIBS_INCLUDES}")

#include_directories("C:/of/libs/glm/include")

#add_executable(${PROJECT_NAME} ${SOURCES})