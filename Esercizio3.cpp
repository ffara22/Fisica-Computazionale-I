/*
c++ -o Esercizio3 Esercizio3.cpp
*/

//--- Nota per i parametri in linea di comando ---
//A = Trapezio
//B = Simpson
//C = Romberg
//D = Legendre
//E = Laguerre

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "quadratore.h"

using namespace std;

double integrando(double x) {
    return pow(x, 7)*exp(-x);
}

//--- Espediente per Laguerre ---
//Non é possibile in linea di principio applicare Laguerre su un intervallo finito, eppure a volte si può maneggiare l'integrale trovando una forma adeguata per ricondursi a un intevallo semiinfinito; questo è il caso: la nuova funzione integrata a partire da a (passato al metodo), è definita su un intervallo semiinfinito e il valore dell'integrale è uguale a quello infinito. Attenzione: questa riscrittura è valida per funzioni che non divergono all'infinito
//Oss: si nota che il calcolo per due punti è altamente impreciso...

double integrando_mod_laguerre(double x) {
    return integrando(x) - integrando(x + 5 - 0); // b = 5; a = 0
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "Inserire argomento dalla riga di comando: lettera del metodo, estremo inferiore, estremo superiore d'integrazione e contatore" << endl;
        return 1;
    }
    
    const char* input = argv[1];
    
    if (static_cast<int>(input[0]) == 65) {
        cout << "Valutazione dell'integrando mediante metodo Trapezio: " << setprecision(16) << Trapezio(integrando, atof(argv[2]), atof(argv[3]), atoi(argv[4])) << endl;
    } if (static_cast<int>(input[0]) == 66) {
        cout << "Valutazione dell'integrando mediante metodo Simpson: " << setprecision(16) << Simpson(integrando, atof(argv[2]), atof(argv[3]), atoi(argv[4])) << endl;
    } if (static_cast<int>(input[0]) == 67) {
        vector <vector <double> > R_res = Romberg(integrando, atof(argv[2]), atof(argv[3]), atoi(argv[4]));
        cout << "Valutazione dell'integrale mediante metodo Romberg: " << setprecision(16) << R_res[atoi(argv[4]) - 1][atoi(argv[4]) - 1] << endl;
    } if (static_cast<int>(input[0]) == 68) {
        cout << "Valutazione dell'integrando mediante metodo Gauss-Legendre: " << setprecision(16) << GaussLegendre(integrando, atof(argv[2]), atof(argv[3]), atoi(argv[4])) << endl;
    } if (static_cast<int>(input[0]) == 69) {
        cout << "Valutazione dell'integrando mediante metodo Gauss-Laguerre: " << setprecision(16) << GaussLaguerre(integrando_mod_laguerre, atof(argv[2]), atoi(argv[4])) << endl;
    }
    return 0;
}
