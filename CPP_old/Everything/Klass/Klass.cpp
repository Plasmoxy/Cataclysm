// Klass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <pmxy.h>
#include <pmxyvec.h>

using namespace std;
using namespace pmxy;

void change(int& a) {
	a = 5;
}

void increment(Vec& v) {
	v.x += 1;
	v.y += 1;
}

int main()
{
	Vec a(1, 1);
	Vec b(2, 3);
	a += b;



    return 0;
}

