// TimeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>


using namespace std;

int main()
{
	// ctime
	time_t t = time(0);
	cout << "millis: " << t << endl;
	cout << "time : " << ctime(&t);

	
    return 0;
}

