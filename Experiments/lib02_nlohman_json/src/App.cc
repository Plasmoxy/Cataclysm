#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
	json xd = {
		{"name", "Sebu"},
		{"age", 19},
	};
	fmt::print("{}", xd.dump(2));

	auto fromstr = "null"_json;


	return 0;
}