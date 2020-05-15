#pragma once

#include "Test.h"

namespace tests {

	class TestLena : public Test {
	public:
		

		TestLena();
		~TestLena();

		void update(float dt) override;
		void render() override;
		void imGuiRender() override;
	};

}