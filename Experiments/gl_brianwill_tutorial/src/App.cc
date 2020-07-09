#include "App.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

using namespace std;

void framebufferSizeCallback(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLuint loadShader(const char* name) {
	stringstream ss;
	
	ss << ifstream(fmt::format("res/{}.vert", name)).rdbuf();
	string vertexSrcStr = ss.str();
	const char* vertexSrc = vertexSrcStr.c_str();
	ss.str("");

	ss << ifstream(fmt::format("res/{}.frag", name)).rdbuf();
	string fragmentSrcStr = ss.str();
	const char* fragmentSrc = fragmentSrcStr.c_str();
	ss.str("");

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

	GLuint shader = loadShader("uniforms");

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,	0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	GLuint vbo, ibo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// this saves the buffers into vao and also saves the layout there
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ==================== Render ==========================

	while (!glfwWindowShouldClose(win)) {

		// imput
		if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(win, true);
		}

		// logic
		GLint loc_changingColor = glGetUniformLocation(shader, "changingColor");

		glUseProgram(shader);
		float time = glfwGetTime();
		glUniform4f(loc_changingColor, 0.0f, sin(time) / 2.0f + 0.5f, 0.0f, 1.0f);
		
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// swap
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// ==================== Cleanup ==========================
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	glfwTerminate();
	return 0;
}