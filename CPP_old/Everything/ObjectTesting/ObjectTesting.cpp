// ObjectTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


class A {
public:
	int a, b;

	A(int a, int b) {
		this->a = a;
		this->b = b;
	}

	virtual void print() {
		std::cout << "a=" << a << " b=" << b << std::endl;
	}

};

class B : public A {
public:
	B(int a, int b) : A(a, b) {}

	virtual void print() {
		std::cout << "this is b derived print " << std::endl;
	}
};

int main()
{
	A* obj = &B(3, 4);
	obj->print(); // will use A's function if not virtual ( virtual gives runtime polymorphism )

	//std::cin.get();
    return 0;
}

