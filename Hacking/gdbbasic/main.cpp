#include <stdio.h>
using namespace std;

bool checkPassword(char* password) {
    return password == "koberec";
}

int main(int argc, char** argv) {
    checkPassword("XD");
}