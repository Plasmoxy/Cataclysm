#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"


namespace tests {

	class TestLena : public Test {
	public:
		Texture* texture;
		Shader* shader;
		VertexBuffer* vbo;
		IndexBuffer* ibo;
		VertexArray* vao;
		float negative = 0;

		TestLena();
		~TestLena();

		void update(float dt) override;
		void render(Renderer& renderer) override;
		void imGuiRender() override;
	};

}