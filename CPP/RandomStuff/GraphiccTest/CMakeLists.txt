cmake_minimum_required(VERSION 2.8)
project(simple)

# glfw testing app
add_executable(glfwxd glfwxd.cpp)
target_link_libraries(glfwxd GL GLU glfw) # link from default ubuntu lib

# glut testing app
add_executable(glutxd glutxd.cpp)
target_link_libraries(glutxd GL GLU glut)

add_executable(ultraSimpleGLFW ultraSimpleGLFW.cpp)
target_link_libraries(ultraSimpleGLFW GL GLU glfw)