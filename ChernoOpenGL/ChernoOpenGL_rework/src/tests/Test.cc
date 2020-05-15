#include "Test.h"
#include "imgui/imgui.h"
#include "fmt/format.h"

namespace tests {

	TestMenu::TestMenu(Test*& currentTest): currentTest(currentTest) {}

	void TestMenu::imGuiRender() {
		for (auto& test : tests) {
			if (ImGui::Button(test.first.c_str())) {
				currentTest = test.second();
			}
		}
	}

}