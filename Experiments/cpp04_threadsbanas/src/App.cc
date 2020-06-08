#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>
using namespace std;

int getRandom(int max) {
	srand(time(nullptr));
	return rand() % max;
}

void executeThread(int id) {
	auto now = chrono::system_clock::now();
	time_t sleepTime = chrono::system_clock::to_time_t(now);
	tm myLocalTime = *localtime(&sleepTime);

	cout << "Thread "    << id
		 <<" Sleep Time" << ctime(&sleepTime) << "\n";
}

int main(int argc, char* argv[]) {
	
	return 0;
}