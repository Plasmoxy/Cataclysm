/*
A+B Problém
Vypočítajte hodnotu a + b.

Vstup
Na začiatku vstupu bude celé číslo n (1 ≤ n ≤ 100) vyjadrujúce počet úloh, ktoré budú nasledovať. Každá úloha je zadaná dvomi celými číslami a a b (|a|, |b| ≤ 1000) oddelené medzerou.

Výstup
Pre každú úlohu vypíšte na samostatný riadok číslo a + b.

Ukážkový vstup
3
1 5
-5 -8
-23 23

Ukážkový výstup
6
-13
0
*/

#include <iostream>

using namespace std;

int main() {

    int pocetZadani = 0;
    cin >> pocetZadani;

    int riesenia[pocetZadani] = {};

    for (int i = 0; i < pocetZadani; i++) {
        int a, b;
        cin >> a >> b;
        riesenia[i] = a + b;
    }

    for (int i = 0; i < pocetZadani; i++) {
        cout << riesenia[i] << endl;
    }
    
}