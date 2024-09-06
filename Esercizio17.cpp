/*
c++ -o Esercizio17 Esercizio17.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "integratore.h"

#define N 3

//--- Condizionamento ---
//Intrinsecamente mal condizionato

//--- Stabilità ---
//Anche variando i dati inziali il moto è generalemente ben confinato e sempre caratterizzato dalla forma a farfalla.

//Non c'è stato bisogno di riscrivere o modificare i termini del problema perchè era già un sistema al primo ordine

double f0(double t, double *v) {
    return -10.*(v[0] - v[1]);
}

double f1(double t, double *v) {
    return -v[0]*v[2] + 28.*v[0] - v[1];
}

double f2(double t, double *v) {
    return v[0]*v[1] - 8./3.*v[2];
}

int main(int argc, char *argv[]) {
    
    double y[N], t_passo, t_i, t_f;
    
    double (*f[N])(double t, double *v)={f0,f1,f2};
    
//    --- Condizioni iniziali ---
    
    y[0] = 1;
    y[1] = -2.75; //Ho fatto variare di epsilon = 0.01 questa coordinata per valutare il condizionamento del problema
    y[2] = 3.7;
    t_i = 0.;
    t_f = 100;
    t_passo = 10000;
    
    integratore(N, y, f, t_i, t_f, t_passo, argv[1]);
    
    return 0;
}
