#ifndef zeri_h
#define zeri_h

#include <cmath>

using namespace std;


//Il metodo prende in ingresso: funzione, minimo, massimo e numero di intervalli in cui dividere il range
void RicercaZeri (double g(double), double xMin, double xMax, int n) {
    double h = (xMax - xMin)/n;
    
    for (int i = 0; i < n; i++) {
        double a = xMin + i*h;
        double b = xMin + (i + 1)*h;
        
        if (g(a)*g(b) < 0) {
            cout << "Zero in (" << a << ", " << b << ")" << endl;
        }
    }
}


double Bisezione(double g(double), double xMin, double xMax, double precisione) {
    double xRif = 0.5 * (xMax + xMin);
    if (abs(xMax - xMin) < precisione){
        return xRif;
    }
    if ((g(xRif)*g(xMax)) < 0){
        return Bisezione(g, xRif, xMax, precisione);
    }
    if ((g(xRif)*g(xMax)) > 0){
        return Bisezione(g, xMin, xRif, precisione);
    } else {
        cout << "Processo inconclusivo..." << endl;
        return xRif;
    }
}


double NewtonRaphson (double g(double), double g_primo(double), double xZero, double precisione) {
    double xRif = xZero;
    double xSuc = xZero - g(xZero)/g_primo(xZero);
    
    while (abs(xSuc - xRif) > precisione) {
        xRif = xSuc;
        xSuc = xRif - g(xRif)/g_primo(xRif);
    }
    
    return xRif;
}

#endif
