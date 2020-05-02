#include <stdio.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {

	if (!glfwInit()) {
		printf("GLFW init err");
		return -1;
	}



	glfwTerminate();
	return 0;
}