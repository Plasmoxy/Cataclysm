#include <iostream>

using namespace std;

char getByte(void *p, int pos) {
    return *( (char*) p + pos );
}

int main() {
    char* s = "abcd";
    cout << getByte(s, 3) << endl;
}