
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);
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

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true); // init GLFW implementation
    ImGui_ImplOpenGL3_Init("#version 330 core"); // init OpenGL impl
    ImGuiIO& io = ImGui::GetIO();
    
    // Scaling for fonts (HDPI)
    // ImFontConfig cfg;
    // cfg.SizePixels = 26;
    // ImFont* defaultFont = io.Fonts->AddFontDefault(&cfg);
    // defaultFont->DisplayOffset.y = 2.0f;

    // shader
    Shader shader("shaders/texture.vert", "shaders/texture.frag");
    shader.bind();

    // texture
    Texture texture("res/lena.png");
    texture.bind(0);
    shader.setUniform1i("u_Texture", 0); // texture slot uniform

    // geometry data...
    float vertices[] = {
        //  x     y    texX  texY
        100.f, 100.f,  0.0f, 0.0f,
        200.f, 100.f,  1.0f, 0.0f,
        200.f, 200.f,  1.0f, 1.0f,
        100.f, 200.f,  0.0f, 1.0f,
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

    // math stuff
    // View matrix - camera transform
    // Model matrix - model transform
    // Projection matrix - projection from model space to gl screen space
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);

    // unbind all, imporant: unbind VAO first because we cannot delete
    // a VBO/IBO that is currently bound to VAO
    va->unbind();
    vb->unbind();
    ib->unbind();
    shader.unbind();

    // Renderer
    Renderer renderer;

    float seconds = 0;
    double mousex, mousey;
    float glMouseX, glMouseY;
    int width, height;
    constexpr float pi = glm::pi<float>();

    glm::vec3 translation(0, 0, 0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Calculations ...
        seconds = clock() * 1.0f / CLOCKS_PER_SEC;
        glfwGetCursorPos(window, &mousex, &mousey);
        glfwGetWindowSize(window, &width, &height);
        glMouseX = ((float)(mousex/width))*2.0f - 1.0f;
        glMouseY = (1.0f - (float)(mousey/height))*2.0f - 1.0f;
        
        // Rendering ...
        renderer.clear();

        model = glm::translate(glm::mat4(1.0f), translation);

        shader.bind();
        shader.setUniform4f("u_Color", 1.0, 0.0, 1.0, 1.0);
        shader.setUniform2f("u_mouse", glMouseX, glMouseY);
        shader.setUniformMat4f("u_MVP", proj * view * model);

        renderer.draw(*va, *ib, shader);

        /*GLint varrayid;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &varrayid);
        fmt::print("current vao = {}\n", varrayid);*/

        // UI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Text("FPS: %.3f", io.Framerate);
            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 100.0f);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
    }

    delete va; // delete VAO first (unbinds the VBO and IBO)
    delete vb;
    delete ib;

    // cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}