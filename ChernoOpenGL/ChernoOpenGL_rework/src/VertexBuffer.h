#pragma once

#include <GL/glew.h>

class VertexBuffer {
public:
	unsigned int rendererId; // id inside the renderer

	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};