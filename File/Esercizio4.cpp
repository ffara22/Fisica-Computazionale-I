/*
c++ -o Esercizio4 Esercizio4.cpp
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
    return (exp(x) + exp(-x))/2.;
}

double integrando_mod_laguerre (double x) {
    return 0.5*(exp(-(x + 3)) - exp(-(x - 3)) + exp(-(x - 8)) + exp(-(x + 8)));
    // b = 8; a = 3
    // Quindi è una funzione costante considerato il peso di Laguerre!
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
        cout << "Valutazione dell'integrando mediante metodo Gauss-Laguerre: " << setprecision(16) << GaussLaguerre(integrando_mod_laguerre, 0,  atoi(argv[4])) << endl; // Ho dovuto imporre io 0 perchè ho molto rimaneggiato l'integrale
    }
    return 0;
}

