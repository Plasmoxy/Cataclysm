#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <Windows.h>

int main(int argc, char* argv[]) {
	MessageBox(nullptr, L"YES ??", L"KYS!", 0);
	OPENFILENAME n;
	GetOpenFileName(&n);
	std::cout << n.lpstrFile;
	return 0;
}