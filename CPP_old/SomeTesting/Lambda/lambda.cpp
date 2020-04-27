#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

void repeat(int times, const function<void ()> &f) {
    for (int i = 0; i < times; i++) {
        f();
    }
}

void change(int &a) {
    a = a + 1;
}

int main() {

    string m = "hello";
    repeat(3, [=](){
        cout << m << endl;
    });

    function<void(int&)> pront = [](int &x) {
        cout << x << endl;
    };

    vector<int> nums{1, 2, 3};

    for_each(nums.begin(), nums.end(), change);
    for_each(nums.begin(), nums.end(), pront);
}