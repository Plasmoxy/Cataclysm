#pragma once

#include <GL/glew.h>

class VertexBuffer {
private:
	GLuint rendererId; // id inside the renderer
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind();
	void unbind();
};