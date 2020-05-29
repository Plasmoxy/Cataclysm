#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
using namespace std;

auto add(int a, int b) { return a + b; }

auto well() -> string {
	return "Well well well";
}

int main(int argc, char* argv[]) {
	auto t = add(1, 2); // int
	cout << well() << endl;
	cout << t << endl;

	return 0;
}