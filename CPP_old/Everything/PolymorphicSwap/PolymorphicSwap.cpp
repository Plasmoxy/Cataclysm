// PolymorphicSwap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

// this is an interface
class Listener {
public:
	// pure virtual function
	virtual void go() = 0;
};

class User : public Listener {
public:
	virtual void go() override {
		std::cout << "HELLO" << std::endl;
	}
};

class Nothing : public Listener {}; // does nothing


void trigger(Listener* l) {
	l->go();
}

void triggerRef(User& u) {
	u.go();
}

int main()
{
	User obj1 = User();
	obj1.go();
	triggerRef(obj1);

	User obj2 = User();
	trigger(&obj2); // works, User implements Listener

	User obj3;
	Listener* obj3_ls = &obj3;
	trigger(obj3_ls); // also works

	//Nothing *nott = &Nothing(); // CANNOT DO THIS, Nothing doesnt implement all interface methods and therefore is abstract
	
    return 0;
}

