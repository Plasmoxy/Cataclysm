#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <boost/optional.hpp>

using boost::optional;

int main(int argc, char* argv[]) {
	optional<int> t = 4;
	fmt::print("{}", *t);
	return 0;
}