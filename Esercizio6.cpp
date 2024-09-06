/*
 c++ -o Esercizio6 Esercizio6.cpp
*/

//--- Nota per i parametri in linea di comando ---
//A = Trapezio
//B = Simpson
//C = Romberg
//D = Laguerre
//E = Hermitte

// Per ottenere un calcolo di precisione e controllo in Trapezio, Simpson e Romberg, si adopera il cambio di variabile che però richiede l'integrazione in 0 dove abbiamo una singolarità integrabile; il problema è affrontato dividendo in intervalli in dipendenza dei punti e "aggiornando" i tre metodi facendo calcolare il primo intervallo a una formula aperta.

//Nel calcolo con Laguerre l'intervallo è ideale, ma non è ideale la funzione perchè comunque tolto il peso ha carattere esponenziale, quindi per raggiungere una buona precisione serve arrivare almeno a 8 punti considerati; in Hermite, è congeniale il peso ma non l'intervallo d'integrazione: attraverso un rimaneggiamento si trova una buona forma che però tolto il peso è di carattere ancora esponenziale, inoltre vi è un punto di discontinuità della derivata in 0; in questo ultimo caso vi è una discepanza sensibile ma minima con 100 punti mentre per meno il risultato non è congeniale

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "quadratore.h"

using namespace std;

double integrando(double x) {
    return pow(x, 5)*exp(-x*x);
}

double zeta(double x) {
    return exp(-x*x);
}

double integrando_mod_intervallofinito(double x) {
    return 0.5*log(x)*log(x);
}

double integrando_mod_hermite(double x) {
    return 0.5*integrando(abs(x) + 3.);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "Inserire argomento dalla riga di comando: lettera del metodo, estremo inferiore, estremo superiore d'integrazione e contatore" << endl;
        return 1;
    }
    
    const char* input = argv[1];
    
    if (static_cast<int>(input[0]) == 65) {
        cout << "Valutazione dell'integrando mediante metodo Trapezio: ";
       
        double a = 0;
        double b = zeta(atof(argv[2]));
        int n = atoi(argv[4]);
        double h = (b - a)/(n - 1);

        cout << setprecision(16) << h*integrando_mod_intervallofinito(a + h/2.) + Trapezio(integrando_mod_intervallofinito, a + h, b, n - 1) << endl;
    } if (static_cast<int>(input[0]) == 66) {
        cout << "Valutazione dell'integrando mediante metodo Simpson: ";
        
        double a = 0;
        double b = zeta(atof(argv[2]));
        int n = atoi(argv[4]);
        
        if (n%2 != 0){
            cout << "Inserire numero pari di punti!" << endl;
            return 0;
        } else {
            double h = (b - a)/(n - 1);
            
            cout << setprecision(16) << h*integrando_mod_intervallofinito(a + h/2.) + Simpson(integrando_mod_intervallofinito, a + h, b, n - 1) << endl;
        }
    } if (static_cast<int>(input[0]) == 67) {
        cout << "Valutazione dell'integrale mediante metodo Romberg: ";
        
        double a = 0;
        double b = zeta(atof(argv[2]));
        int n = atoi(argv[4]);
        double h = (b - a)/pow(2, n);
        
        vector <vector <double> > R_res = Romberg(integrando_mod_intervallofinito, a + h, b, n);
        
        cout << setprecision(16) << h*integrando_mod_intervallofinito(a + h/2.) + R_res[n - 2][n - 2] << endl;
    } if (static_cast<int>(input[0]) == 68) {
        cout << "Valutazione dell'integrando mediante metodo Gauss-Laguerre: " << setprecision(16) << GaussLaguerre(integrando, atof(argv[2]), atoi(argv[4])) << endl;
    } if (static_cast<int>(input[0]) == 69) {
        cout << "Valutazione dell'integrando mediante metodo Gauss-Hermite: " << setprecision(16) << GaussHermite(integrando_mod_hermite, atoi(argv[4])) << endl;
    }
    return 0;
}
