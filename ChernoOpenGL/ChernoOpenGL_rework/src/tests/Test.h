#pragma once

#include <vector>
#include <string>
#include <fmt/format.h>
#include <functional>

namespace tests {

	class Test {
	public:

		Test() {}
		virtual ~Test() {}

		virtual void update(float dt) {};
		virtual void render() {};
		virtual void imGuiRender() {};
	};

	class TestMenu : public Test {
	public:
		std::vector<std::pair<std::string, std::function<Test*()>>> tests;
		Test*& currentTest;

		TestMenu(Test*& currentTest);

		void imGuiRender() override;

		template<typename T>
		void registerTest(const std::string& name) {
			fmt::print("Registering test: {}\n", name);
			tests.push_back(std::make_pair(name, []() {
				return new T();
			}));
		};
	};

}