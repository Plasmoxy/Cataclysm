/*

*/


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static int CreateShader(const std::string& vShader, const std::string& fShader)
{
    GLuint program = glCreateProgram();   
    return 0;
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

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the current bound buffer in a specific drawing mode
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();  
    }

    glfwTerminate();
    return 0;
}