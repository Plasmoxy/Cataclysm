// ProcessHackTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

int main() {
	SetConsoleTitle(TEXT("XDD"));
	int data = 54; // Dummy Data
	while (true) {
		std::cout << &data << " = " << data << std::endl;
		_getch();
	} return 0x00;
}

