/*
c++ -o Esercizio15 Esercizio15.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "integratore.h"

#define N 2

// Si è fatto variare i parametri per entrare nelle fasi notabile dell'oscillatore forzate/smorzato di sovrasmorzamento e di sotto smorzamento

#define gamma 0.1
#define A 0.4

using namespace std;

double f0(double t, double *v) {
    return v[1];
}

//--- Condizionamento ---
//Il pendolo semplice è ben condizionato. Aggiungendo smorzamento il problema persiste ben condizionato (esiste oure sempre una soluzione analitica). Con l'aggiunta della forzante la situazione si complica ma esistono soluzioni analitiche.

//--- Stabilità ---
//I metodi non hanno mai troppo bisogno di diminuire il passo, l'unico caso è quello di una forzante particolarmente complessa.

// Per eseguire tutti i casi è sufficente commentare i pezzi di forzante e attrito così da ricondursi al problema in esame

double f1(double t, double *v) {
    return -sin(v[0])- 2*gamma*v[1] + A*sin(2./3.*t);
}

int main(int argc, char *argv[]) {
    
    double y[N], t_passo, t_i, t_f;
    
    double (*f[N])(double t, double *v)={f0,f1};
    
//    --- Setting dei dati del problema ---
    
    y[0] = 0.;
    y[1] = 1.;
    t_passo = 400;
    t_i = 0.;
    t_f = 40.;
    
    integratore(N, y, f, t_i, t_f, t_passo, argv[1]);
    
    return 0;
}
