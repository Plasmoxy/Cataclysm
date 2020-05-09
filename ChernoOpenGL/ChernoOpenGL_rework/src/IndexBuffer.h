#pragma once

#include <GL/glew.h>

class IndexBuffer {
public:
	unsigned int rendererId; // id inside the renderer
	unsigned int count;

	IndexBuffer(unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
};