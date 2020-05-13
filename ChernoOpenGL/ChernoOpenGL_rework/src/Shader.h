#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <fmt/format.h>
#include <GL/glew.h>

class Shader {
public:
	std::string vertexPath;
	std::string fragmentPath;
	unsigned int rendererId = 0;

	// caching
	std::unordered_map<std::string, GLint> uniformLocationCache;

	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	void bind() const;
	void unbind() const;

	// uniforms
	GLint getUniformLocation(const std::string& uniformName);
	void setUniform1i(const std::string& name, int v);
	void setUniform1f(const std::string& name, float v);
	void setUniform2f(const std::string& name, float a, float b);
	void setUniform4f(const std::string& name, float a, float b, float c, float d);

	// util
	static std::string tryReadFile(const std::string& filepath);
	static GLuint compileShader(unsigned int type, const std::string& source);
	static GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
};