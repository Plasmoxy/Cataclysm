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
	std::string namePath;
	unsigned int rendererId = 0;

	// caching
	std::unordered_map<std::string, GLint> uniformLocationCache;

	Shader(const std::string& name);
	~Shader();

	void bind() const;
	void unbind() const;

	// uniforms
	void setUniform4f(const std::string& name, float a, float b, float c, float d);
	
	GLint getUniformLocation(const std::string& uniformName);

	// util
	static std::string tryReadFile(const std::string& filepath);
	static GLuint compileShader(unsigned int type, const std::string& source);
	static GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
};