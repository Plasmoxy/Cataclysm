// BoostThingy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost/integer/common_factor.hpp>

int main()
{
	std::cout << boost::integer::gcd(2838, 2320) << std::endl;
	std::cin.get();
    return 0;
}

