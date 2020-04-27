
#include <iostream>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include "TestLibrary.hpp"

int main()
{
	fmt::print("Init glfw: {}\n", glfwInit());

	int a = 5;
	fmt::print("Hello xd {}\n", a);
	// pronts Hello 5

	prontTestLibrary();
}