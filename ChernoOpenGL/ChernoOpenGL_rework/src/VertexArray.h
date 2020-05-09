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

	// componentCount = how many components of this type there are
	// within this attribute
	template <typename T>
	void addAttrib(unsigned int componentCount);

	template<>
	void addAttrib<float>(unsigned int componentCount) {
		attributes.push_back({ GL_FLOAT, componentCount, false });
		stride += componentCount * VertexAttribute::getSizeOfGLType(GL_FLOAT);
	}

	template<>
	void addAttrib<unsigned int>(unsigned int componentCount) {
		attributes.push_back({ GL_UNSIGNED_INT, componentCount, false });
		stride += componentCount * VertexAttribute::getSizeOfGLType(GL_UNSIGNED_INT);
	}

	template<>
	void addAttrib<unsigned char>(unsigned int componentCount) {
		attributes.push_back({ GL_UNSIGNED_BYTE, componentCount, false });
		stride += componentCount * VertexAttribute::getSizeOfGLType(GL_UNSIGNED_BYTE);
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