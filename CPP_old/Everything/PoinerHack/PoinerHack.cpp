#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
	int newData = 61; // new value
	HWND wVictim = FindWindow(0, TEXT("XDD"));
	if (wVictim == 0x00) {
		std::cerr << "Victim not found." << std::endl;
	}
	else {
		DWORD pId;
		GetWindowThreadProcessId(wVictim, &pId);
		HANDLE pVictim = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
		if (!pVictim) {
			std::cerr << "Process error." << std::endl;
		}
		else {
			int result = WriteProcessMemory(pVictim,
				(LPVOID)0x012FFDB4, // Victim Variable Address
				&newData,
				(DWORD)sizeof(newData),
				NULL);
			if (result>0x00) {
				std::clog << "Result: Success." << std::endl;
			}
			else {
				std::cerr << "Result: Error." << std::endl;
			}
			CloseHandle(pVictim);
		}
	}
	_getch();
	return 0x00;
}