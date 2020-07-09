#include "App.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebufferSizeCallback(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* SIMPLE_VERT = R"EOF(
	#version 330 core
	layout(location = 0) in vec3 pos;
	
	void main() {
		gl_Position = vec4(pos, 1.0);
	}
)EOF";


const char* SIMPLE_FRAG = R"EOF(
	#version 330 core

	out vec4 color;

	void main() {
		color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
)EOF";

GLuint createShader(const char* vertexSrc, const char* fragmentSrc) {
	// shaders
	int success;
	char infoLog[512];

	// -> vertex
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexSrc, nullptr);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, nullptr, infoLog);
		cout << "Vertex shader compile err" << infoLog << endl;
	}

	// -> fragment
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentSrc, nullptr);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, nullptr, infoLog);
		cout << "Vertex shader compile err" << infoLog << endl;
	}

	GLuint shader = glCreateProgram();
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, nullptr, infoLog);
		cout << "Shader linking err :" << infoLog << endl; 
	}
	glDeleteShader(vs);
	glDeleteShader(fs);

	return shader;
}

int main(int argc, char* argv[]) {

	// ==================== Init ==========================

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Brian OpenGL Tutorial", nullptr, nullptr);
	if (!win) {
		cout << "Error creating glfw win." << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(win);
	glfwSetFramebufferSizeCallback(win, framebufferSizeCallback);

	// GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD init err.";
		glfwTerminate();
		return -1;
	}

	// ==================== Data ==========================

	GLuint shader = createShader(SIMPLE_VERT, SIMPLE_FRAG);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,	0.5f, 0.0f,
	};

	GLuint vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// this saves the buffers into vao and also saves the layout there
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ==================== Render ==========================

	while (!glfwWindowShouldClose(win)) {

		// imput
		if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(win, true);
		}
		
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// swap
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// ==================== Cleanup ==========================
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
	return 0;
}