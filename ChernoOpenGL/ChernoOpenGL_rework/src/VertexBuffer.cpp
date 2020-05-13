#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    // VBO (slot GL_ARRAY_BUFFER) -> VAO
    glGenBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &rendererId);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
