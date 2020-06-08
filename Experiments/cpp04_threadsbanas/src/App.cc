#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>
using namespace std;

int resource = 0;
mutex resourceMtx;

void threadA() {
	lock_guard lock(resourceMtx);
	cout << "Thread A res = 4\n";
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Thread A end\n";
}

void threadB() {
	lock_guard lock(resourceMtx);
	cout << "Thread B res = 5\n";
	this_thread::sleep_for(chrono::seconds(4));
	cout << "Thread B end\n";
}


int main(int argc, char* argv[]) {
	// lock resource
	thread ta(threadA);
	thread tb(threadB);


	ta.join();
	tb.join();
	return 0;
}