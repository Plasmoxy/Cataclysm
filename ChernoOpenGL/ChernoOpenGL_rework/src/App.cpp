
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

#include "GLDebugMessageCallback.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

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

    // blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // data...
    float vertices[] = {
    //      x      y   texX  texY
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
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
    layout.addAttrib<float>(2); // pos
    layout.addAttrib<float>(2); // texture pos
    va->setVBO(*vb, layout);

    // IBO (slot GL_ELEMENT_ARRAY_BUFFER) -> VAO
    IndexBuffer* ib = new IndexBuffer(indices, 6);
    va->setIBO(*ib);

    // stuff
    Shader shader("shaders/texture.vert", "shaders/texture.frag");
    Texture texture("res/lena.png");

    // texture
    shader.bind();
    texture.bind(0);
    shader.setUniform1i("u_Texture", 0); // texture slot uniform

    // unbind all, imporant: unbind VAO first because we cannot delete
    // a VBO/IBO that is currently bound to VAO
    va->unbind();
    vb->unbind();
    ib->unbind();
    shader.unbind();

    Renderer renderer;

    float r = 0.0f;
    double mousex, mousey;
    int width, height;
    float glMouseX, glMouseY;

    while (!glfwWindowShouldClose(window))
    {
        glfwGetCursorPos(window, &mousex, &mousey);
        glfwGetWindowSize(window, &width, &height);
        glMouseX = (mousex/width)*2.0f - 1.0f;
        glMouseY = (1.0f - mousey/height)*2.0f - 1.0f;
        
        if (r > 1.0f) r = 0.0f;
        r += 0.05f;

        renderer.clear();

        shader.bind();
        shader.setUniform4f("u_Color", 1.0, 0.0, 1.0, 1.0);
        shader.setUniform2f("u_mouse", glMouseX, glMouseY);
        renderer.draw(*va, *ib, shader);

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