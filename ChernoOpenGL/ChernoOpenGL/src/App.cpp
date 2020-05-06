/*

	"The vertices of triangles are associated not only with spatial position
	but also with other values used to render the object correctly."
	vertex buffer layout:
	x, y,
	x, y,
	x, y,
	...


	vertexattribpointer:
		index = index of the attribute inside vertex
			   -> (this works as attribute IDENTIFIER inside shader)
		size = 2 (floats per vertex) = how many components per vertex
		type = type of data attributes inside vertex
		stride = bytesize per vertex = 2*sizeof(float) per vertex
		pointer = offset to the vertex attribute in bytes
				  (pointer mem offset inside single vertex)
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define Log(x) std::cout << x << std::endl

static GLFWwindow* InitGL();

static std::string LoadShader(const std::string& shaderName)
{
	std::fstream fs("res/shaders/" + shaderName);
	std::stringstream ss;
	ss << fs.rdbuf();
	return ss.str();
}

static GLuint CompileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// error handling
	int result; glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length; glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		
		// alloc message array to stack, not heap
		char* message = (char*) _malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader: " << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0; // zero id = no shader
	}

	return id;
}

static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	// shaders are linked to programs so we don't need the shaders now
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	auto window = InitGL(); if (!window) return -1;


	float positions[] = {
		-0.5f, -0.5f, // vertex 0
		 0.0f,  0.5f, // vertex 1
		 0.5f, -0.5f,  // vertex 2
	};

	GLuint buffer;
	glGenBuffers(1, &buffer); // generate id for buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // set array buffer to be this buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); // copy the data to buffer (copies to gpu)

	// the x attrib is bound to attrib index 0 now
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0); // enable that attribute

	GLuint programSimple = CreateShader(
		LoadShader("simple_v.glsl"),
		LoadShader("simple_f.glsl")
	);
	glUseProgram(programSimple);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// render primitives from array data, (rendermode, startVertexIndex, endVertexIndex)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(programSimple);

	glfwTerminate();
	return 0;
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		// recompile shader on space press
		if (key == GLFW_KEY_SPACE) {
			GLuint programSimple = CreateShader(
				LoadShader("simple_v.glsl"),
				LoadShader("simple_f.glsl")
			);
			glUseProgram(programSimple);
			std::cout << "Recompiled shader." << std::endl;
		}
	}
	else if (action == GLFW_RELEASE) {

	}
}

// setup opengl context, glfw, return window or nullptr
static GLFWwindow* InitGL()
{
	if (!glfwInit()) return nullptr;

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		Log("Error initializing GLEW");
		return nullptr;
	}

	// we got context
	Log(glGetString(GL_VERSION));

	// setup gl and events
	glfwSetKeyCallback(window, KeyCallback);

	return window;
}