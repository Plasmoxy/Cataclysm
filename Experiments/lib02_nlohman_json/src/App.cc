#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
	json xd;
	xd["pi"] = 3.14;
	fmt::print("{}", xd.to_st);
	return 0;
}