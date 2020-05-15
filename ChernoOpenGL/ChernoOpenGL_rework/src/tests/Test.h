#pragma once

namespace test {

	class Test {
	public:

		Test() {}
		virtual ~Test() {}

		virtual void update(float dt) {};
		virtual void render() {};
		virtual void imGuiRender() {};
	};

}