#include <iostream>
#include <bitset>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
std::string dumpNum(T x) {
    const int xsize = sizeof(x)*8; // n bytes * 8 bits
    int xval = (int)x;

    std::stringstream s;
    s << "dec: " << xval;
    s << " hex: " << std::hex << xval;
    s << " bin: " << std::bitset<xsize>(xval);

    return s.str();
}

int main() {
    char positive = 3;
    char negative = -3;
    
    cout << "Positive: " << dumpNum(positive) << endl;
    cout << "Negative: " << dumpNum(negative) << endl;
}