// sololearnstuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Hello {
public:
	void sayHi()
	{
		cout << "hi" << endl;
	}
};

int main()
{
	Hello h;
	h.sayHi();

	cin.get();
    return 0;
}

