
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

#include "GLDebugMessageCallback.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void) {

    /* Initialize GLFW */
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync


    // Init GLEW
    if (glewInit() != GLEW_OK) fmt::print("GLEW init error");
    printf("GL version: %s\n", glGetString(GL_VERSION));

    // GL setup
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // data...
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };
    
    // VAO
    VertexArray* va = new VertexArray();

    // VBO -> VAO
    VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.addAttrib<float>(2);
    va->setVBO(*vb, layout);

    // IBO (slot GL_ELEMENT_ARRAY_BUFFER) -> VAO
    IndexBuffer* ib = new IndexBuffer(indices, 6);
    va->setIBO(*ib);

    // shader
    Shader shader("shaders/red");

    // unbind all, imporant: unbind VAO first because we cannot delete
    // a VBO/IBO that is currently bound to VAO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);

    float r = 0.0f;
    double xpos, ypos;
    int width, height;

    while (!glfwWindowShouldClose(window))
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT);

        if (r > 1.0f) r = 0.0f;
        r += 0.05f;

        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        va->bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(0));
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * 4));

        /*GLint varrayid;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &varrayid);
        fmt::print("current vao = {}\n", varrayid);*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete va; // delete VAO first (unbinds the VBO and IBO)
    delete vb;
    delete ib;

    glfwTerminate();
    return 0;
}