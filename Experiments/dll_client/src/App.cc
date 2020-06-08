#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include "DllFromTemplate.h"
using namespace std;

int main(int argc, char* argv[]) {
	
	cout << "DllFromTemplate -> " << DllFromTemplate_add(1, 2) << endl;

	return 0;
}