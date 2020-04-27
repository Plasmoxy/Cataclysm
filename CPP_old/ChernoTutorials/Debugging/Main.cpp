#include <iostream>
#define Log(x) std::cout << x << std::endl

int add(int a, int b) {
	Log("kys");
	return a + b;
}

int main() {
	int a = 9;
	a++;
	const char* t = "hello";

	for (int i = 0; i < strlen(t); i++) {
		Log(t[i]);
	}

}