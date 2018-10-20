#include <iostream>
#include <string>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Trojuholnik {
public:
    double a=0, b=0, c=0, alfa=0, beta=0, gama=0;

    Trojuholnik() {}
    
    // vypocet vsetkych ostatnych dat trojuholnika podla viet
    void vypocitaj() {

        int strany = (a!=0) + (b!=0) + (c!=0);
        int uhly = (alfa!=0) + (beta!=0) + (gama!=0);

        // veta SSS
        if (strany == 3) {
            alfa = kosinusovaVeta(a, b, c);
            beta = kosinusovaVeta(b, a, c);
            gama = M_PI - alfa - beta;
        }
        
        else if (strany >= 2 && uhly >= 1) {
            int s1, s2, u;
            
        }

        
    }

    // a^2 = b^2 + c^2 - 2bc*cos(alfa)
    // vracia alfu (oproti strane a)
    // a -> protilahla strana uhlu ktory chceme ziskat
    double kosinusovaVeta(double a, double b, double c) {
        return acos(
            (b*b + c*c - a*a) / (2*b*c)
        );
    }

    // a/sin(alfa) = b/sin(beta)
    // vracia stranu a ak zadame alfu, b, betu
    double sinusovaVetaStrana(double alfa, double b, double beta) {
        return (b * sin(alfa)) / sin(beta);
    }

    // vracia uhol alfa ak zadame a, b, betu
    double sinusovaVetaUhol(double a, double b, double beta) {
        return asin(
            (a * sin(b)) / b
        );
    }

    void vypis() {
        cout << "-- trojuholnik --" << endl;
        cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
        cout << "alfa=" << alfa*180/M_PI << "deg, beta=" << beta*180/M_PI << "deg, gama=" << gama*180/M_PI << "deg" << endl;
        cout << "-----------------" << endl;
    }
};

Trojuholnik vstupTrojuholnik() {
    Trojuholnik troj;

    cout << "Zadavajte data (napiste ok pre ukoncenie) :" << endl;

    bool hotovo = false;
    while (!hotovo) {
        cout << ">"; // indikator zadavania

        string line;
        getline(cin, line);

        if (line == "ok") {
            break;
        }

        // spracuj prikaz priradenia
        // ak existuje delimiter
        if ( line.find("=") != string::npos )  {
            string p = line.substr(0, line.find("=")); // zober premennu
            line.erase(0, line.find("=") + 1); // zmaz z toho stringu vsetok ten assign bordel ohladom premennej
            // ( tym padom mi v line stringu zostavaju data na parsovanie)
            
            double hodnota = 0;
            try {
                hodnota = stold(line);
            } catch(invalid_argument) {
                cout << "Chybna hodnota premennej !" << endl;
                continue;
            }

            if (p == "a") {
                troj.a = hodnota;
            } else if (p == "b") {
                troj.b = hodnota;
            } else if (p == "c") {
                troj.c = hodnota;
            }
            
            else if (p == "alfa") {
                troj.alfa = hodnota;
            } else if (p == "beta") {
                troj.beta = hodnota;
            } else if (p == "gama") {
                troj.gama = hodnota;
            }
        }
    }

    cout << "Data zadane !" << endl;

    return troj;

}

int main() {
    Trojuholnik t = vstupTrojuholnik();
    t.vypocitaj();
    t.vypis();
}