#pragma once

#include <vector>
#include <cassert>
#include <GL/glew.h>
#include "VertexBuffer.h"

struct VertexAttribute {
	GLuint type = 0;
	unsigned int componentCount = 0;
	bool normalized = false;

	static unsigned int getSizeOfGLType(GLuint type) {
		switch (type) {
			case GL_FLOAT:		   return 4;
			case GL_UNSIGNED_INT:  return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		assert(false);
		return 0;
	}
};

class VertexBufferLayout {
public:
	// attribute indexes are the same as in VAO
	std::vector<VertexAttribute> attributes;
	unsigned int stride = 0; // bytesize of entire layout (all attribs)

	VertexBufferLayout() = default;

	// attribType for example is GL_FLOAT etc.
	// componentCount = how many components of this type there are
	// within this attribute
	void addAttrib(GLuint type, unsigned int componentCount) {
		auto normalize = type == GL_UNSIGNED_BYTE;
		attributes.push_back({type, componentCount, normalize});
		stride += componentCount * VertexAttribute::getSizeOfGLType(type);
	}
};

class VertexArray {
public:
	GLuint rendererId = 0;

	VertexArray();
	~VertexArray();
	
	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};