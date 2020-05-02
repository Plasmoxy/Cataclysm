#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	
	int t = 4;
	wprintf(L"Kačka a vĺčik plávajú cez vŕbu a jedia mäso, %d\n", t);;

	return 0;
}