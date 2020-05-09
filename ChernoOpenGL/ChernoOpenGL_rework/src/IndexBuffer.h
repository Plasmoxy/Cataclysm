#pragma once

#include <GL/glew.h>

class IndexBuffer {
public:
	GLuint rendererId = 0; // id inside the renderer (in our case OpenGL)
	unsigned int count = 0;

	IndexBuffer(unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
};