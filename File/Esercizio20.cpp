/*
c++ -o Esercizio20 Esercizio20.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "zeri.h"

using namespace std;

//Per rendere più comprensibile il codice si è voluto definire la norma quadra che compare in diverse valutazioni dei passaggi, come nella condizione del while
double NormaQuadra(double x, double y) {
    return x*x + y*y;
}

int main(int argc, char const *argv[]) {
    
    int N = 2000, K = 45;
    double epsilon = 0.001;
    double h = (2. + 2.)/N;
    
    FILE *file = fopen("Esercizio20.txt", "w");
    if (file == NULL) {
        cout << "Errore nell'apertura del file." << endl;
        return 1;
    }
    
    double xZero, yZero;
    
    for (int i = 0; i < N; i++) {
        xZero = i*h - 2.;
        for (int j = 0; j < N; j++) {
            yZero = j*h - 2.;
            
            // --- Passo Zero ---
            double xRif = xZero, yRif = yZero;
            double xSuc = 1./3.*(2*xZero + (xZero*xZero - yZero*yZero)/pow(NormaQuadra(xZero, yZero), 2.));
            double ySuc = 1./3.*(2*yZero - 2*xZero*yZero/pow(NormaQuadra(xZero, yZero), 2.));
            
            // --- Iterazione ---
            int nIterazioni = 0;
            while (sqrt(NormaQuadra(xSuc - xRif, ySuc - yRif)) > epsilon && nIterazioni < K) {
                nIterazioni += 1;
                
                xRif = xSuc;
                yRif = ySuc;
                xSuc = 1./3.*(2*xRif + (xRif*xRif -yRif*yRif)/pow(NormaQuadra(xRif, yRif), 2.));
                ySuc = 1./3.*(2*yRif - 2*xRif*yRif/pow(NormaQuadra(xRif, yRif), 2.));
            }
            
            fprintf(file, "%d %d %f %f %f %f %d\n", i, j, xZero, yZero, xSuc, ySuc, nIterazioni);
            
        }
    }
    
    fclose(file);
    
    return 0;
}



