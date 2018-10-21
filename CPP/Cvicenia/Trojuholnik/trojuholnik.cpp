#include <iostream>
#include <string>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Trojuholnik {
public:
    double a, b, c; // strany trojuholnika
    double alfa, beta, gama; // uhly su ulozene v radianoch

    Trojuholnik():
        a(0), b(0), c(0),
        alfa(0), beta(0), gama(0)
    {}
    
    // vypocet vsetkych ostatnych dat trojuholnika podla viet
    // TODO: treba dajak inak to vymysliet
    void vypocitaj() {

        // tri strany
        if (a && b && c) {
            alfa = kosinusovaVetaUhol(a, b, c);
            beta = kosinusovaVetaUhol(b, a, c);
            gama = M_PI - alfa - beta;
        }

        // a, b + uhly
        else if (a && b && alfa) {
            beta = sinusovaVetaUhol(b, a, alfa);
            gama = M_PI - alfa - beta;
            c = sinusovaVetaStrana(gama, a, alfa);
        }
        else if (a && b && beta) {
            alfa = sinusovaVetaUhol(a, b, beta);
            gama = M_PI - alfa - beta;
            c = sinusovaVetaStrana(gama, a, alfa);
        }
        else if (a && b && gama) {
            c = kosinusovaVetaStrana(gama, a, b);
            alfa = sinusovaVetaUhol(a, c, gama);
            beta = sinusovaVetaUhol(b, c, gama);
        }

        // a, c + uhly
        else if (a && c && alfa) {
            gama = sinusovaVetaUhol(c, a, alfa);
            beta = M_PI - alfa - gama;
            b = sinusovaVetaStrana(beta, a, alfa);
        }
        else if (a && c && beta) {
            b = kosinusovaVetaStrana(beta, a, c);
            alfa = sinusovaVetaUhol(a, b, beta);
            gama = sinusovaVetaUhol(c, b, beta);
        }
        else if (a && c && gama) {
            alfa = sinusovaVetaUhol(a, c, gama);
            beta = M_PI - alfa - gama;
            b = sinusovaVetaStrana(beta, c, gama);
        }

        // b, c + uhly
        else if (b && c && alfa) {
            a = kosinusovaVetaStrana(alfa, b, c);
            beta = sinusovaVetaUhol(b, a, alfa);
            gama = M_PI - alfa - beta;
        }
        else if (b && c && beta) {
            gama = sinusovaVetaUhol(c, b, beta);
            alfa = M_PI - beta - gama;
            a = sinusovaVetaStrana(alfa, b, beta);
        }
        else if (b && c && gama) {
            beta = sinusovaVetaUhol(b, c, gama);
            alfa = M_PI - beta - gama;
            a = sinusovaVetaStrana(alfa, c, gama);
        }

        else {
            cout << "CHYBA: Treba zadat aspon 3 parametre trojuholnika!" << endl;
        }
    }

    // a^2 = b^2 + c^2 - 2bc*cos(alfa)
    // vracia uhol protilahly strane a ak b,c zvieraju tento uhol
    double kosinusovaVetaUhol(double a, double b, double c) {
        return acos(
            (b*b + c*c - a*a) / (2*b*c)
        );
    }

    // vracia stranu protihahlu uhlu gama ak mame gamu, a jej prilahle strany b,a
    double kosinusovaVetaStrana(double gama, double b, double a) {
        return sqrt(
            b*b + a*a - 2*b*a*cos(gama)
        );
    }

    // a/sin(alfa) = b/sin(beta)
    // vracia stranu protihahlu alfe ak beta je protilahly uhol strane b
    double sinusovaVetaStrana(double alfa, double b, double beta) {
        return (b * sin(alfa)) / sin(beta);
    }

    // vracia uhol alfa protihahly strane a ak beta je protilahly uhol strane b
    double sinusovaVetaUhol(double a, double b, double beta) {
        return asin(
            (a * sin(beta)) / b
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

    cout << "Zadavajte data (napiste ok pre ukoncenie) (uhly su v stupnoch) :" << endl;
    troj.vypis();

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
                troj.alfa = hodnota/180*M_PI;
            } else if (p == "beta") {
                troj.beta = hodnota/180*M_PI;
            } else if (p == "gama") {
                troj.gama = hodnota/180*M_PI;
            }
        }
    }

    cout << "Data zadane !" << endl;

    return troj;

}

int main() {
    cout << "Vypocet vseobecneho trojuholnika - S.Petrik - C++" << endl;
    Trojuholnik t = vstupTrojuholnik();
    t.vypocitaj();
    t.vypis();
}