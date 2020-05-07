/*

*/


#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <ctime>
#include "TEST_SHADERS.h"

static GLuint compileShader(unsigned int type, const std::string& source)
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

static GLuint createShaderProgram(const std::string& vShader, const std::string& fShader)
{
    GLuint program = glCreateProgram();   
    GLuint vs = compileShader(GL_VERTEX_SHADER, vShader);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fShader);

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
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW init error." << std::endl;
    printf("GL version: %s\n", glGetString(GL_VERSION));
    
    // define vertices
    float vertices[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f,
    };

    // create buffer
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0); // enable the attribute array (attribute) !!!

    // Shaders config
    GLuint shader = createShaderProgram(VSHADER_BASIC, FSHADER_BASIC);
    GLint uniTimeSeconds = glGetUniformLocation(shader, "timeSeconds");
    glUseProgram(shader);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glUniform1f(uniTimeSeconds, clock() / (float)CLOCKS_PER_SEC);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw the current bound buffer in a specific drawing mode
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();  
    }

    // delete the shader at the end
    glDeleteShader(shader);

    glfwTerminate();
    return 0;
}