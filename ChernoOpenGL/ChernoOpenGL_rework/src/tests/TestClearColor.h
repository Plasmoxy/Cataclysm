#pragma once

#include "Test.h"

namespace test {

	class TestClearColor : public Test {
	public:
		float clearColor[4] = {0, 0, 0, 1.0f};

		TestClearColor();
		~TestClearColor();

		void update(float dt) override;
		void render() override;
		void imGuiRender() override;
	};

}