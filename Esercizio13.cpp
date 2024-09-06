/*
c++ -o Esercizio13 Esercizio13.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "quadratore.h"
#include "casual.h"

#define pi 3.1415926535897932

using namespace std;


double coseno(double x) {
    return x*cos(x);
}

double seno(double x) {
    return x*sin(x);
}

double arcoseno(double x) {
    return asin(x);
}

double arcocoseno (double x) {
    return acos(x);
}

double HOM (double f(double), double fmax, double a, double b, int Nmax) {
    int nhit = 0;
    
    for (int i = 0; i < Nmax; i++) {
        
        double x = RandIntervallo(a, b);
        double y = RandIntervallo(0, fmax);
        
        if (y < f(x)) {
            nhit += 1;
        }
    }
    
    return (b - a)*fmax*nhit/Nmax;
}

int main(int argc, char const *argv[]) {
    
    vector <vector <double> > R1 = Romberg(coseno, 0 , pi/2., 5);
    vector <vector <double> > R2 = Romberg(seno, 0 , pi, 5);
    
    
    cout << "Primo integrale. " << endl;
    cout << "Romberg 32 punti: " << setprecision(16) << R1[4][4] << endl;
    cout << "HOM con sampling." << endl;
    for (int i = 100; i < 10000000; i*=10) {
        cout << i << "\t"  << setprecision(16) << HOM(arcoseno, pi, 0, 1, i) << endl;
    }
    
    cout << endl;
    
    cout << "Secondo integrale. " << endl;
    cout << "Romberg 32 punti: " << setprecision(16) << R2[4][4] << endl;
    cout << "HOM e con sampling." << endl;
    for (int i = 100; i < 10000000; i*=10) {
        cout << i << "\t"  << setprecision(16) << HOM(arcocoseno, pi, -1, 1, i) << endl;
    }
    
    return 0;
}
