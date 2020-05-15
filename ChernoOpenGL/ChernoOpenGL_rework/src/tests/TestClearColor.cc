#include "TestClearColor.h"
#include <GL/glew.h>
#include <imgui/imgui.h>

namespace tests {

	TestClearColor::TestClearColor() {

	}

	TestClearColor::~TestClearColor() {

	}

	void TestClearColor::update(float dt) {

	}

	void TestClearColor::render(Renderer& renderer) {
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	}

	void TestClearColor::imGuiRender() {
		ImGui::ColorEdit4("Clear Color", clearColor);
	}
}