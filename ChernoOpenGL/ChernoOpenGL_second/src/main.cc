/*

*/


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
#include "TEST_SHADERS.h"

std::string tryReadFile(const std::string& filepath)
{
    std::stringstream ss;
    std::ifstream fs(filepath);
    if (!fs) {
        fmt::print("Error loading file: {}\n", filepath);
        return "";
    }
    ss << fs.rdbuf();
    return ss.str();
}

GLuint compileShader(unsigned int type, const std::string& source)
{
    // create shader
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();

    // specify shader source for created shader and compile it
    glShaderSource(id, 1, &src, nullptr); //length=NULL means source is null-terminated
    glCompileShader(id);

    // handle compilation errors
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); // returns parameter from shader obj
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        fmt::print("Failed to compile {} shader:\n{}\n",
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment"),
            message
        );

        glDeleteShader(id); // delete it
        delete[] message;
        return 0; // 0 = failure
    }

    return id;
}

GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    GLuint program = glCreateProgram();   
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    // attach and link shaders to the program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // they are linked to the program, we can delete them from memory
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    /* Initialize GLFW */
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // Init GLEW
    if (glewInit() != GLEW_OK) fmt::print("GLEW init error");
    printf("GL version: %s\n", glGetString(GL_VERSION));

    // Callback error handling
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);
    
    // define vertices
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    // define indexes = instructions on how to reuse vertices into drawing triangles
    // (also called elements)
    // NOTE: make sure this is always an unsigned int[] !!!
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    // create and bind VAO (see below)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // create vertex buffer object (vertex buffer) from vertices[]
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind to a bind target before using!
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attributes = how data inside v. buffer is modelled.
    // Typically the gpu provides max 16 4-component vertex attributes.
    // This provides data layout for each vertex, while we have unknown amount
    // of vertices.
    // = 64 components per vertex
    // eg. position atribute has -> x and y -> 2 components
    // -> glVertexAttribPointer sets a SINGLE attribute of vertex
    // index = index of attribute (max 15)
    // size = count of components in the attribute
    // type = data type of each component i.e. GL_FLOAT
    // normalized = auto normalization
    // stride = complete byte size of a vertex (all attributes)
    // pointer = ? byte offset to the attribute in the vertex (void*)
    // NOTE: to lay out data, use struct combined with offsetof macro
    // by default, Vertex Array Object (VAO) at idx 0 is created automatically
    // (only in GL-compatibility profile, not in GL core profile)
    // -> if we don't have VAO bound currently, we can get INVALID OPERATION error
    // IMPORTANT: glVertexAttribPointer binds current VAO and VBO !!!
    // "index 0 of current VAO is now bound to current VBO (GL_ARRAY_BUFFER)"
    glEnableVertexAttribArray(0); // enable the attribute array (attribute) !!!
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    // create index buffer object from indices[]
    // NOTE: GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER are separate OpenGL
    // binding targets (many types).
    // NOTE: an opengl object inside GPU is often represented by its GLuint ID.
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Shaders config
    GLuint testShader = createShaderProgram(
        tryReadFile("shaders/test.vert"),
        tryReadFile("shaders/test.frag")
    );
    GLint u_Secs = glGetUniformLocation(testShader, "u_Secs");
    GLint u_Color = glGetUniformLocation(testShader, "u_Color");

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // UNBIND everything (for demo purposes)
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    float r = 0.0f;
    double xpos, ypos;
    int width, height;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        // fmt::print("mouse[{} {}] win[{} {}]\n", xpos, ypos, width, height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Example:
        // draw the current bound vertex buffer in a specific drawing mode
        // -> DOES NOT use any indices
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        // bind stuff that we're gonna use
        glUseProgram(testShader);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glUniform1f(u_Secs, clock() / (float) CLOCKS_PER_SEC);

        if (r > 1.0f) r = 0.0f;
        r += 0.05f;

        // draw current bound VBO using current bound IBO indices
        // note: indices paramter is an OFFSET of first index of currently bound GL_ELEMENT_ARRAY_BUFFER, not a pointer to some array 
        glUniform4f(u_Color, r, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const void*)(3*sizeof(unsigned int)));

        // example: ANOTHER draw call, it is not efficient to change uniforms and issue another draw call, that problem is solved by passing different values in VBO (but like 100 draws is fine)
        glUniform4f(u_Color, 1.0f - r, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}