#include <iostream>
#include "somelib/lib.hpp"
#include "vectorutil.hpp"

using namespace std;

int main() {
    Vec2f A(1, 2);
    Vec2f B(3, 4);

    Vec2f c = A + B;

    cout << c.toString() << endl;
}