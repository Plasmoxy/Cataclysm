
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cassert>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "GLDebugMessageCallback.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"

int main(void) {

    /* Initialize GLFW */
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(960, 540, "Cherno GL Rework", nullptr, nullptr);

    HWND windowHandle = glfwGetWin32Window(window);
    unsigned int windowDpi = GetDpiForWindow(windowHandle);
    fmt::print("Running on Windows with DPI: {}\n", windowDpi);


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
    glEnable(GL_DEPTH_TEST);

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

    // Stuff
    Renderer renderer;
    tests::Test* currentTest;
    tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->registerTest<tests::TestClearColor>("Clear Color");

    bool controlsOpen = true;
    float seconds = 0;
    double mousex, mousey;
    float glMouseX, glMouseY;
    int width, height;
    constexpr float pi = glm::pi<float>();

    while (!glfwWindowShouldClose(window))
    {
        // Setup of frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Calculations ...
        seconds = clock() * 1.0f / CLOCKS_PER_SEC;
        glfwGetCursorPos(window, &mousex, &mousey);
        glfwGetWindowSize(window, &width, &height);
        glMouseX = ((float)(mousex/width))*2.0f - 1.0f;
        glMouseY = (1.0f - (float)(mousey/height))*2.0f - 1.0f;
        
        // Rendering ...
        if (currentTest == testMenu) glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderer.clear();
        if (currentTest) {
            currentTest->update(0.0f);
            currentTest->render();
            
            ImGui::Begin("Tests");
            // if we arent in test menu, draw button and if it is clicked, ...
            if (currentTest != testMenu && ImGui::Button("<-")) {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->imGuiRender();
            ImGui::End();
        }

        // End of frame
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}