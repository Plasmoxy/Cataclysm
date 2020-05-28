#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>

class Shallow {
public:
	int a = 0;
	int* ptr = nullptr;

	Shallow() {
		fmt::print("Default constr.\n");
	}

	// works the same
	/*Shallow(const Shallow& that) {
		fmt::print("Copy constr.\n");
		a = that.a;
		ptr = that.ptr;
	}*/
	Shallow(const Shallow& that) = default;

	// works the same
	/*Shallow& operator=(const Shallow& that) {
		fmt::print("Assignment oprtr.\n");
		return *this;
	}*/
	Shallow& operator=(const Shallow& that) = default;

	void pront() {
		fmt::print("Shallow a={}\n", a);
	}
};

int main(int argc, char* argv[]) {
	
	Shallow x;
	x.a = 4;
	x.ptr = new int;

	Shallow y = x;

	Shallow c;
	c = x;

	x.pront();
	y.pront();
	c.pront();

	fmt::print("&x.a = {}\n", (void*) &x.a);
	fmt::print("&y.a = {}\n", (void*) &y.a);
	fmt::print("&x.ptr = {}\n", (void*) &x.ptr);
	fmt::print("&y.ptr = {}\n", (void*) &y.ptr);

	return 0;
}