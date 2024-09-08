/*
c++ -o Esercizio8 Esercizio8.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

#include "quadratore.h"

#define pi 3.14159265358979323846

using namespace std;

int fattoriale(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n*fattoriale(n - 1);
    }
}


int semifattoriale(int n) {
    if (n == 0) {
        return 1;
    } if (n == 1) {
        return 1;
    } else {
        return n*semifattoriale(n-2);
    }
}


double SferaAnalitica(int dim) {
    if (dim%2 == 0) {
        return pow(pi,dim/2)/(fattoriale(dim/2));
    } else {
        return (pow(2, (dim + 1)/2)*pow(pi, (dim - 1)/2.))/semifattoriale(dim);
    }
}


double RandIntervallo(double min, double max){
  return min + (max - min)*rand()/static_cast<double>(RAND_MAX);
}


double EmisferaMDimensionale(vector<double> x) {
    double coord = 0;
    for (int i = 0; i < x.size(); i++) {
        coord += x[i]*x[i];
    }
    if (coord >= 1) {
        return 0;
    } else {
        return sqrt(1 - coord);
    }
}

// La sfida più grande è stata costruire la funzione con un vector di coordinate e permettere l'integrazione con Midpoint senza la dipendenza dalla dimensione; l'algoritmo implementato nella libreria infatti e stato parecchio difficoltoso. Per montecarlo invece tutto è risultato più semplice perchè vi era totale indipendenza dalle coordinate ed è stato sufficente riempire il vector volta per volta con coordinate casuali.


int main(int argc, char const *argv[]){
    
    int Nmax = 100000;
    
    for (int m = 2; m < 11; m++) {
        
        cout << "Dimensione della sfera: " << m << endl;
        
        //    --- Crude Monte Carlo ---
        clock_t startMonteCarlo = clock();
        
        double sum = 0, integrale = 0;
        
        vector <double> x;
        x.resize(m, 0);
        for (int k = 0; k < Nmax; k++) {
            
            for (int i = 0; i < m - 1; i++) {
                x.push_back(RandIntervallo(0, 1));
            }
            
            sum += EmisferaMDimensionale(x);
            x.clear();
        }
        
        integrale = pow(2, m)*sum/Nmax;
        
        clock_t stopMonteCarlo = clock();
        double durataMonteCarlo = static_cast<double>(stopMonteCarlo - startMonteCarlo) / CLOCKS_PER_SEC;
        
        //      --- Risultati ---
        cout << "Metodo analitico: " << SferaAnalitica(m) << endl;
        cout << "Metodo Monte Carlo: " << integrale << endl;
        cout << "Tempo Monte Carlo: " << durataMonteCarlo << " secondi" << endl;
        
        
        //       --- Midpoint ---
        clock_t startMidpoint = clock();
        
        integrale = pow(2, m)*MidpointGrigliaSimmetrica(EmisferaMDimensionale, m - 1, 10);
        
        clock_t stopMidpoint = clock();
        double durataMidpoint = static_cast<double>(stopMidpoint - startMidpoint) / CLOCKS_PER_SEC;
        
        //      --- Risultati ---
        cout << "Metodo del Midpoint: " << integrale << endl;
        cout << "Tempo Midpoint: " << durataMidpoint << " secondi" << endl;
        
        cout << endl;
    }
    
    return 0;
}
