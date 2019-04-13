#include <iostream>
using namespace std;

template <typename T>
struct Vec {

    T x = (T)0, y = (T)0, z = (T)0;

    Vec() {}
    Vec(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    void print() {
        std::cout << "[ " << x << ", " << y << ", " << z << " ]" << endl;
    }

    Vec<T> cpy() {
        return Vec(x, y, z);
    }

    Vec<T> add(Vec<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
};

struct Vec3i : Vec<int> {
    Vec3i() : Vec() {};
    Vec3i(int x, int y, int z) : Vec(x, y, z) {};
};

struct Vec3f : Vec<float> {
    Vec3f() : Vec() {};
    Vec3f(float x, float y, float z) : Vec(x, y, z) {};
};

int main() {
    cout << "int " << sizeof(int) << endl;
    cout << "unsigned int " << sizeof(unsigned int) << endl;
    cout << "short " << sizeof(short) << endl;
    cout << "long " << sizeof(long) << endl;

    Vec3i obj = Vec3i(1, 2, 3);
    cout << "class Vec3i " << sizeof(Vec3i) << endl;
    cout << "obj Vec3i " << sizeof(obj) << endl;
    
    auto v1 = Vec3i(1, 2, 3);
    auto v2 = Vec3i(2, 3, 4);
    auto vf = Vec3f(1.0f, 2.0f, 1.0f);

    auto sum = v1.cpy().add(v2);

    cout << "sum of vectors" << endl;
    sum.print();
}