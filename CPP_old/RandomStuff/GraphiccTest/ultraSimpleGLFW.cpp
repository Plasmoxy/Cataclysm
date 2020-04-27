#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* window;


void render();
int main() {
    glfwInit();
    window = glfwCreateWindow(600, 300, "Hello", NULL, NULL);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLES);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(10.0f, 10.0f, 0.0f);
        glVertex3f(30.0f, 40.0f, 0.0f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void render() {
    
}