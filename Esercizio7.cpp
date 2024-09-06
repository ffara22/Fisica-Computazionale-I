/*
c++ -o Esercizio7 Esercizio7.cpp
*/

//--- Nota per i parametri in linea di comando ---
//D = Laguerre
//E = Hermitte

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "quadratore.h"

using namespace std;

double integrando(double x) {
    return pow(x, 14)*exp(-x*x);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "Inserire argomento dalla riga di comando: lettera del metodo, estremo inferiore, estremo superiore d'integrazione e contatore" << endl;
        return 1;
    }
    
    const char* input = argv[1];
    
    if (static_cast<int>(input[0]) == 68) {
        cout << "Valutazione dell'integrando mediante metodo Gauss-Laguerre: " << setprecision(16)  << GaussLaguerre(integrando, atof(argv[2]), atoi(argv[4])) << endl;
    } if (static_cast<int>(input[0]) == 69) {
        cout << "Valutazione dell'integrando mediante metodo Gauss-Hermite: " << setprecision(16)  << 0.5*GaussHermite(integrando, atoi(argv[4])) << endl;
    }
    return 0;
}
