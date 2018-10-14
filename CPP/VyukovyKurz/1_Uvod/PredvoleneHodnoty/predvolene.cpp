#include <iostream>

using namespace std;

int main() {
    int a; // reserve random int in memory, we don't know what will be there we just take it
    cout << a << endl; // should print what data was in memory at that reserved place ( that we didnt clean up )
    return 0;
}