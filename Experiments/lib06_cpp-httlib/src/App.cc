#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <httplib.h>
#include <future>

using namespace httplib;

int main(int argc, char* argv[]) {
	Server app;

	app.Get("/", [](const Request& req, Response& res) {
		res.set_content("Welcome", "text/plain");
	});

	auto serverTask = std::async(std::launch::async, [&]() {
		app.listen("localhost", 80);
	});
	
	fmt::print("Listening on port 80.\n");
	std::cin.get();
	app.stop();
	serverTask.get();
	return 0;
}