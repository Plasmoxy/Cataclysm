/* 
 * Tento program popisuje využitie najnižšieho bitu údaja na zistenie párnosti.
 * V reálnej situácii treba použiť výraz s modulom : bool parne = x%2 == 0
 * 
 * Intel x86 používa little-endian endianitu pre adresovanie bajtových častí premennej.
 * v adrese premennej je jej najnižší (posledný) bajt,
 * v adrese+1 je predposledný, atď.
 * 
 * btw:
 * (najvyšší bajt) MSB -> 0101 1010 1110 <- LSB (najnižší bajt)
 */


#include <iostream>
#include <bitset>
using namespace std;

// tympadom ->
template<typename T>
bool jeParne(T x) {
    char lastByte = x;
    return !(lastByte & 0b0001);
}

int main() {
    int a = 8; // nejaké číslo

    // najprv si zoberiem jeho posledný bajt
    char lastByte = a; // doslova stačí nacastovať a do bajtu, lebo x86 je little endian ( castuje sa koniec premennej )

    // teraz si zoberiem posledný bit (stále je to char ale nafiltrujem si bity cez AND hradlo)
    // vďaka filtrácii bool bajt bude mať hodnotu buď 0b0000 alebo 0b0001 čo sa zhoduje s jeho typom
    // tým pádom operátor negácie ! bude kompletne fungovať
    // ak je 0 tak je cislo parne, ak 1 tak nie -> ešte si to znegujem
    bool parne = !(lastByte & 0b0001);
    cout << (string)(parne ? "a je parne" : "a je neparne") << endl;


    // pomocou funkcie
    int integer = 3000;
    int longint = 3000001L;
    
    cout << "parny integer? " << integer << " -> " << jeParne(integer) << endl;
    cout << "parny long? " << longint << " -> " << jeParne(longint) << endl;

    int moduloInt = 3001;

}