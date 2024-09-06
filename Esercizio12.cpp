/*
c++ -o Esercizio12 `root-config --glibs --cflags` Esercizio12.cpp
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "casual.h"
#include "statistiche.h"

#include "TGraph.h"
#include "TH1F.h"
#include "TCanvas.h"

#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

#define pi 3.1415926535897932

using namespace std;


double f(double x) {
    return 1./sqrt(pi)*exp(-x*x);
}

double l(double r) {
    return 1./pi*exp(-r*r);
}

double L(double r) {
    return 1 - exp(-r*r);
}

double LInv(double r) {
    return sqrt(-log(1 - r));
}



//  --- Importance sampling ---

double g(double x) {
    if (x < 1) {
        return 1./sqrt(pi);
    } else {
        return 1./sqrt(pi)*x*exp(1 - x*x);
    }
}

double G(double x) {
    if (x < 1) {
        return 1./sqrt(pi);
    } else {
        return 1./(2*sqrt(pi))*(3 - exp(1 - x*x));
    }
}

double GInv(double x) {
    if (x < 1./sqrt(pi)) {
        return sqrt(pi)*x;
    } else {
        return sqrt(1 - log(3. - 2.*sqrt(pi)*x));
    }
}



int main(int argc, char const *argv[]) {
    
    TH1F * h1 = new TH1F("esatto", "", 70, -3., 3.);
    TH1F * h2 = new TH1F("accept/rejct", "", 70, -3., 3.);
    
    double fmax = 1./sqrt(pi);
    vector <double> x_esatto, x_ar;
    
    for (int i = 0; i < 1000000; i++) {
        
//        --- Esatto ---
        
        double r_rand = RandMFI(LInv, 0, 1);
        double x_rand = r_rand*cos(2*pi*RandIntervallo(0., 1.));
        x_esatto.push_back(x_rand);
        h1->Fill(x_rand);
        
//        --- Accept/Reject ---
        
        int sgn = rand();
        if (sgn%2 == 0) {
            sgn = 1;
        } else {
            sgn = -1;
        }
        double x = RandMFI(GInv, 0, 3./(2.*sqrt(pi)));
        double y = RandIntervallo(0, g(x));
        if (y < f(sgn*x)) {
            x_ar.push_back(sgn*x);
            h2->Fill(sgn*x);
        }
    }
    
    cout << "Medie:" << "\t\t\t" << Media(x_esatto) << "\t" << Media(x_ar) << endl;
    cout << "Secondo momento:" << "\t" << M2(x_esatto) << "\t" << M2(x_ar) << endl;
    cout << "Quarto momento:" << "\t\t" << M4(x_esatto) << "\t" << M4(x_ar) << endl;
    
    
//    --- Opzioni di Fit ---
    
    TF1 * d1 = new TF1("Esatto", "gaus(0)", -3., 3.);
    TFitResultPtr fit_result1 = h1->Fit(d1, "S+");
    if(fit_result1->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    TF1 * d2 = new TF1("AR", "gaus(0)", -3., 3.);
    TFitResultPtr fit_result2 = h2->Fit(d1, "S+");
    if(fit_result2->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
//    --- Graficazione dei risultati ---
    
    TCanvas * c = new TCanvas();
    
    h1->SetFillColor(kBlue + 1);
    h1->Draw();
    gStyle->SetOptFit(kTRUE);
    c->Print("Es12_Esatto.png", "png");
    
    h2->SetFillColor(kBlue + 1);
    h2->Draw();
    gStyle->SetOptFit(kTRUE);
    c->Print("Es12_AR.png", "png");
    
    delete h1;
    delete h2;
    delete d1;
    delete d2;
    delete c;
    
    return 0;
}
