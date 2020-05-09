#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    // VBO (slot GL_ARRAY_BUFFER) -> VAO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
}

void VertexBuffer::bind() {
}

void VertexBuffer::unbind() {
}
