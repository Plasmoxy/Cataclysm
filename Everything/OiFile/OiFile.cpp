// OiFile.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

template <typename T>
void writeFile(const char * name, T data) {
	std::stringstream ss;
	ss << data;
	std::ofstream ofs;
	ofs.open(name);
	
	if (ofs.is_open()) {
		ofs << ss.str();
		ofs.close();
	}
}

int main()
{
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	std::stringstream ss;
	ss << "The local date and time is: " << dt << std::endl;
	writeFile("DATE.txt", ss.str());

	
    return 0;
}

