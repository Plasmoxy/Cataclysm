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
    char negative_using_memory = ~positive + 1; // bitwise negation and add 1 to achieve negative sign
    
    cout << "Positive: " << dumpNum(positive) << endl;
    cout << "Negative: " << dumpNum(negative) << endl;
    cout << "Negative using memory: " << dumpNum(negative_using_memory) << endl << endl;

    
    // what about negating operators ?
    char num = 0b10001100;
    char num_bitwise = ~num;
    char num_negated = !num;

    cout << "Num: " << dumpNum(num) << endl;
    cout << "Num bitwise: " << dumpNum(num_bitwise) << endl;
    cout << "Num negated: " << dumpNum(num_negated) << endl;

}