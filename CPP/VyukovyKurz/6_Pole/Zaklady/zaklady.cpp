#include <iostream>
using namespace std;

template <typename T>
void vypis(T x[], int N) {
    cout << "[";
    for (int i = 0; i<N; i++) {
        cout << x[i] << " ";
    }
    cout << "]" << endl;
}

int main() {
    int pole[10]{0};
    vypis(pole, 10);
}