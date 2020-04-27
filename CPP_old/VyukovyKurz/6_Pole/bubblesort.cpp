#include <iostream>

using namespace std;

int vypis(int* p, int N) {
    for (int i = 0; i<N; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
}

void bubbleSort(int *pole, int n, bool debug=false) {
    int m = n;
    // zoradujeme z pohladu i na i+1
    bool vymena = false;
    do {
        vymena = false; // bola uskutocnena vymena (vybublala nova hodnota)? mam posunut hranicu?
        m--;
        
        for (int i = 0; i<m; i++) {
            // vymen ak vacsie
            if (pole[i] > pole[i+1]) {
                int temp = pole[i+1];
                pole[i+1] = pole[i];
                pole[i] = temp;
            } else {
                continue;
            }

            if (debug) vypis(pole, n);

            vymena = true; // treba posunut hranicu
        }

    } while(vymena);
}

int main() {
    const int N = 8;
    int pole[N] = {6, -1, 2, -5, 2, 2, 11, 9};

    bubbleSort(pole, N, true);
}