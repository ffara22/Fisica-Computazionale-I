/*
c++ -o Esercizio19 Esercizio19.cpp
*/

//--- Nota per i parametri in linea di comando ---
//A = Ricerca degli intervalli
//B = Stima degli zeri

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>

#include "zeri.h"

//Per cambiare da un problema all'altro basta commentare il problema che non vogliamo trattare

//double F(double x) {
//    return 2.*x*x - 3.*x + 1.;
//}
//
//double Fprimo(double x) {
//    return 4.*x - 3.;
//}

double F(double x) {
    return (46189. * pow(x, 10) - 109395. * pow(x, 8) + 90090. * pow(x, 6) - 30030. * pow(x, 4) + 3465. * pow(x, 2) - 63.) / 256.;
}

double Fprimo(double x) {
    return (230945. * pow(x, 9) - 765765. * pow(x, 7) + 270270. * pow(x, 5) - 60060. * pow(x, 3) + 3465. * x) / 128.;
}

using namespace std;

// --- Stabilità di Newton-Raphson ---
//Si è notato come il metodo risponda in modo differente a seconda della scelta di xZero. Nel codice è stato implementato un controllo che stampa a schermo se lo zero non è contenuto nell'intervallo.

int main(int argc, char const *argv[]) {
    
    if (argc < 5) {
        cout << "Inserire argomento dalla riga di comando: A(per ricerca intervalli)/B(per ricerca zeri), xMin, xMax e N(punti su cui dividere l'itervallo)/precisione" << endl;
        return 1;
    }
    
    const char* input = argv[1];
    
    if (static_cast<int>(input[0]) == 65) {
        cout << "Ricerca degli intervalli... " << endl;
        RicercaZeri(F, atof(argv[2]), atof(argv[3]), atoi(argv[4]));
    } if (static_cast<int>(input[0]) == 66) {
        cout << "Stima dello zero nell'intervallo dato con metodo di Newton-Raphson: ";
        
        double xZero = atof(argv[3]) + atof(argv[2]))/2.;
        double StimaNW = NewtonRaphson(F, Fprimo, xZero, atof(argv[4]));
        cout << setprecision(16) << StimaNW << endl;
        if (StimaNW >= atof(argv[3]) || StimaNW <= atof(argv[2])) {
            cout << "Il processo ha riscontrato un errore causato dalla scelta di xZero..." << endl;
        }
        
        cout << "Stima dello zero nell'intervallo dato con metodo di Bisezione: " << setprecision(16) << Bisezione(F, atof(argv[2]), atof(argv[3]), atof(argv[4])) << endl;
    }
    return 0;
}
