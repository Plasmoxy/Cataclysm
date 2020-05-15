#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
public:

	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib,
			  const Shader& shader) const;
};