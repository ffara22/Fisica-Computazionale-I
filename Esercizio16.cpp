/*
c++ -o Esercizio16 Esercizio16.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "integratore.h"

#define N 2
#define alpha 0.5
#define beta 0.7
#define gamma 0.03

//--- Stabilità ---
//Far convergere i metodi è stato molto complicato, si è dovuto trovare un compromesso tra tempo di calcolo e precisione. Si sarebbe potuto stimare la probabilità con cui soluzioni anche non coincidenti fossero vicine a una possibile soluzione reale.

//Il metodo è sostanzialmente simile a quelli precedenti, quindi un leap-frog, facendo variari i parametri sopra

using namespace std;

double f0(double t, double *v) {
    return v[1];
}

double f1(double t, double *v) {
    return -(alpha - beta*cos(t))*sin(v[0]) - gamma*v[1];
}

int main(int argc, char *argv[]) {
    
    double y[N], t_passo, t_i, t_f;
    
    double (*f[N])(double t, double *v)={f0,f1};
    
//    --- Setting dei dati del problema ---
    
    y[0] = 0.;
    y[1] = 0.1;
    t_passo = 30000000;
    t_i = 0.;
    t_f = 300.;
    
    integratore(N, y, f, t_i, t_f, t_passo, argv[1]);
    
    return 0;
}
