#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;
using msec = std::chrono::milliseconds;

void sleep(int ms) {
	this_thread::sleep_for(msec(ms));
}

char* getTime() {
	time_t t = time(0);
	return asctime(localtime(&t));
}

int main() {

	cout << getTime() << endl;
	sleep(3000);
	cout << getTime() << endl;

	return 0;
}