// OiFile.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <iomanip> // put_time



std::string timeAndDateString()
{
	time_t	now = time(0);
	char	buf[30];

	ctime_s(buf, 30, &now);
	return std::string(buf);
}

template <typename T>
void writeFile(const char * name, T data) {
	std::stringstream	ss;
	std::ofstream		ofs;

	ss << data;
	ofs.open(name);
	
	if (ofs.is_open()) {
		ofs << ss.str();
		ofs.close();
	}
}

int main()
{

	std::stringstream ss;
	ss << "The local date and time is: " << timeAndDateString() << std::endl;
	writeFile("DATE.txt", ss.str());

	
    return 0;
}

