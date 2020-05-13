
#include "VertexArray.hpp"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &rendererId);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &rendererId);
}

void VertexArray::setVBO(const VertexBuffer& vbo,
						 const VertexBufferLayout& layout) {
	bind();
	vbo.bind();
	
	const auto& attribs = layout.attributes;
	unsigned int offset = 0;

	for (unsigned int i = 0; i < attribs.size(); i++) {
		const auto& attr = attribs[i];

		// Enable this attrib array in VAO and set its layout
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attr.componentCount, attr.type, attr.normalized,
							  layout.stride, (const void*) offset);

		// increase offset by bytesize of specified attribute
		// we have to recalculate this again because we need incremental
		// offsets every iteration
		offset += attr.componentCount * VertexAttribute::getSizeOfGLType(attr.type);
	}
}

void VertexArray::setIBO(const IndexBuffer& ibo) {
	bind();
	ibo.bind();
}

void VertexArray::bind() const {
	glBindVertexArray(rendererId);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}
