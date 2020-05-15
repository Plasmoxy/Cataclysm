#include "TestLena.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace tests {

	TestLena::TestLena() {
		texture = new Texture("res/lena.png");
		shader = new Shader("shaders/texture.vert", "shaders/texture.frag");
		shader->bind();
		texture->bind(0);
		shader->setUniform1i("u_Texture", 0);

		// geometry data...
		float vertices[] = {
			//  x     y    texX  texY
			-50.f, -50.f,  0.0f, 0.0f,
			 50.f, -50.f,  1.0f, 0.0f,
			 50.f,  50.f,  1.0f, 1.0f,
			-50.f,  50.f,  0.0f, 1.0f,
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		vbo = new VertexBuffer(vertices, sizeof(vertices));
		ibo = new IndexBuffer(indices, sizeof(indices));
		vao = new VertexArray();

		VertexBufferLayout layout;
		layout.addAttrib<float>(2); // pos
		layout.addAttrib<float>(2); // texture pos
		vao->setIBO(*ibo);
		vao->setVBO(*vbo, layout);

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -100.0f, 100.0f);
		glm::mat4 view(1.0f);
		glm::mat4 model(1.0f);
		shader->setUniformMat4f("u_MVP", proj * view * model);
	}

	TestLena::~TestLena() {
		delete vao; delete ibo; delete vbo;
		delete shader; delete texture;
	}

	void TestLena::update(float dt) {

	}

	void TestLena::render(Renderer& renderer) {
		shader->bind();
		shader->setUniform1f("u_Negative", negative);
		
		renderer.draw(*vao, *ibo, *shader);
	}

	void TestLena::imGuiRender() {
		ImGui::Text("Lena XDDD");
	}

}