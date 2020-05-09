#pragma once

#include <GL/glew.h>

class VertexBuffer {
public:
	GLuint rendererId = 0; // id inside the renderer

	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};