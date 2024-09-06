#ifndef quadratore_h
#define quadratore_h

#include <fstream>
#include <cmath>


using namespace std;

double Trapezio(double f(double), double a, double b, int N) {
    if (N < 2){
        return 1;
    } else {
        double h = (b - a)/(N - 1) ;
        double res = (f(b) + f(a));
        for (int i = 2.; i < N; i = i + 1) {
            res += 2.*f(a + (i-1)*h);
        }
        
        return 0.5*h*res;
    }
}

double Simpson(double f(double), double a, double b, int N) {
    if (N < 3){
        return 1;
    } if (N%2 == 0) {
        cout << "Non è possibile eseguire Simpson con un numero pari di punti, inserire un numero dispari" << endl;
        return 1;
    } else {
        double h = (b-a)/(N-1);
        double res = (f(b) + f(a));
        for (int i = 2; i < N; i++) {
            if (i%2 == 0) {
                res += 4*f(a + (i-1)*h);
            } else {
                res += 2*f(a + (i-1)*h);
            }
        }
        return h*res/3.;
    }
}



//  --- Metodo di Romberg ---
//Ricordiamo che il metodo calcola suddividendo l'integrazione su n=2^j intervalli

vector <double> JTrapezio(double f(double), double a, double b, int j) {

    double h, sum;
    
    vector <double> T;
    T.resize(j + 1);
    T[0] = 0.5*(b - a)*(f(a) + f(b));
    
    for (int i = 1; i <= j; i++) {
        h = (b - a)/pow(2, i);
        sum = 0;
        for (int k = 1; k <= pow(2, i)/2; k++) {
            sum = sum + f(a + h*(2*k - 1));
        }
        
        T[i] = 0.5*T[i-1] + h*sum;
    }
    
    return T;
}


vector <vector <double> > Romberg(double f(double), double a, double b, int j) {
    vector <vector <double> > R(j, vector<double>(j, 0));
    vector <double> T = JTrapezio(f, a, b, j);

    for (int i = 0; i < j; i++) {
        R[i][0] = T[i];
    }
    
    for (int q = 1; q < j; q++) {
        for (int i = q; i < j; i++) {
            R[i][q] = (pow(4, q)*R[i][q-1] - R[i-1][q-1])/(pow(4, q) - 1);
        }
    }
    
    return R;
}


//--- Metodo Midpoint ---
//Il metodo prende in inpunt una funzione a m-1 (m dimensione del problema) variabili e calcola attraverso una griglia simmetrica il valore dell'integrale; m-1 è dunque la dimensione della griglia e n il numero di intervalli per ogni linea coordinata. E' però necessario normalizzare lo spazio d'integrazione: il volume di integrazione deve essere unitario e incerneato nello 0 vettoriale.

double MidpointGrigliaSimmetrica(double f(vector<double>), int m, int n) {
    double h = 1./n, sum = 0;
    
    vector<double> x;
    x.resize(m - 1, 0);
    
    for (int j = 0; j < pow(n, m); j++) {
        
        double indice = j;
        
        for (int i = 0; i < m; i++) {
            int z = indice/pow(n, m - 1 - i);
            indice = indice - z*pow(n, m - 1 - i);
            x.push_back(z*h + h/2.);
        }
        
        sum += f(x);
        x.clear();
    }
    
    return sum*pow(h, m);
}


//--- Quadratore Gaussiano ---

double GaussLegendre(double f(double), double a, double b, int j) {
    vector <double> x;
    vector <double> w;
    
    fstream fLegendre;
    fLegendre.open("ZeriPesiLegendre.txt");
    while (true) {
        double leggi = 0.;
        fLegendre >> leggi;
        if (static_cast<int>(leggi) == j){
            for (int i = 0; i < j; i++) {
                fLegendre >> leggi;
                x.push_back(leggi);
                fLegendre >> leggi;
                w.push_back(leggi);
            }
            break;
        }
        
        if (fLegendre.eof() == true) break;
    }
    
    double sum = 0;
    for (int i = 0; i < j; i++) {
        sum += 0.5*(b - a)*w[i]*f(0.5*(x[i] + 1.)*(b - a) + a); // un (b-a)/2 è termine di jacobiano della trasformazione per l'integrale!
    }
    
    return sum;
    
}


double GaussLaguerre(double f(double), double a, int j) {
    vector <double> x;
    vector <double> w;
    
    fstream fLaguerre;
    fLaguerre.open("ZeriPesiLaguerre.txt");
    while (true) {
        double leggi = 0.;
        fLaguerre >> leggi;
        if (static_cast<int>(leggi) == j){
            for (int i = 0; i < j; i++) {
                fLaguerre >> leggi;
                x.push_back(leggi);
                fLaguerre >> leggi;
                w.push_back(leggi);
            }
            break;
        }
        
        if (fLaguerre.eof() == true) break;
    }
    
    
    double sum = 0;
    for (int i = 0; i < j; i++) {
        sum += w[i]*f(x[i] + a)*exp(x[i]);
    }
    
    return sum;
    
}


double GaussHermite(double f(double), int j) {
    vector <double> x;
    vector <double> w;
    
    fstream fHermite;
    fHermite.open("ZeriPesiHermite.txt");
    while (true) {
        double leggi = 0.;
        fHermite >> leggi;
        if (static_cast<int>(leggi) == j){
            for (int i = 0; i < j/2; i++) {
                fHermite >> leggi;
                x.push_back(leggi);
                x.push_back(-leggi);
                fHermite >> leggi;
                w.push_back(leggi);
                w.push_back(leggi);
                
        
            }
            break;
        }
        
        if (fHermite.eof() == true) break;
    }
    
    
    double sum = 0;
    for (int i = 0; i < j; i++) {
        sum += w[i]*f(x[i])*exp(x[i]*x[i]);
    }
    
    return sum;
    
}

#endif
