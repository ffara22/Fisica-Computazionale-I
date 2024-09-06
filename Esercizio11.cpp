/*
c++ -o Esercizio11 `root-config --glibs --cflags` Esercizio11.cpp
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "casual.h"

#include "TGraph.h"
#include "TH1F.h"
#include "TCanvas.h"

#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

using namespace std;

// Si è seguito l'utilizzo il metodo della funzione inversa (MFI): generare numeri casuali tra 0 e 1 e, usando l'inverso della comulativa associata alla distribuzione che si vuole generare, generare numeri proporzionalmente sull'intervallo x.


//Scritte in questo modo per poter fare i fit
double D1(double * x, double * par) {
    return par[0]*exp(-x[0]*par[1]);
}

double D2(double * x, double * par) {
    return par[0]*x[0]*exp(-par[1]*x[0]*x[0]);
}


double C1(double x) {
    return (1./1. - exp(-2.))*(1. - exp(-x));
}

double C2(double x) {
    return (1. - exp(-x + 1.));
}

double C3(double x) {
    return (1. - exp(-x*x));
}


double InvC1(double x) {
    return -log(1 - (1. - exp(-2))*x);
}

double InvC2(double x) {
    return -log(1.- x) + 1.;
}

double InvC3(double x) {
    return sqrt(log(1./(1.- x)));
}

int main(int argc, char const *argv[]) {
    
    TH1F * h1 = new TH1F("distribuzione 1", "", 50, 0., 2.2);
    TH1F * h2 = new TH1F("distribuzione 2", "", 50, 0.5, 10);
    TH1F * h3 = new TH1F("distribuzione 3", "", 50, 0., 3);
    
    for (int i = 0; i < 10000; i++) {
        
        h1->Fill(RandMFI(InvC1, 0, 1));
        h2->Fill(RandMFI(InvC2, 0, 1));
        h3->Fill(RandMFI(InvC3, 0, 1));

        
    }
    
    
    
//    --- Opzioni di Fit ---
    
    TF1 * d1 = new TF1("esponenziale decrescente", D1, 0, 4, 2);
    d1->SetParName(0, "a");
    d1->SetParName(1, "b");
    TFitResultPtr fit_result1 = h1->Fit(d1, "S+");
    if(fit_result1->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    TF1 * d2 = new TF1("esponenziale decrescente", D1, 0.5, 10, 2);
    d2->SetParameter(0, 6000);
    d2->SetParameter(1, 1.);
    d2->SetParName(0, "a");
    d2->SetParName(1, "b");
    TFitResultPtr fit_result2 = h2->Fit(d2, "S+");
    if(fit_result2->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    TF1 * d3 = new TF1("x*e^(-x^2)", D2, 0, 6, 2);
    d3->SetParName(0, "a");
    d3->SetParName(1, "b");
    TFitResultPtr fit_result3 = h3->Fit(d3, "S+");
    if(fit_result1->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    
    
//    --- Graficazione dei risultati ---
    
    TCanvas * c = new TCanvas();
    
    h1->SetFillColor(kBlue + 1);
    h1->Draw();
    gStyle->SetOptFit(kTRUE);
    c->Print("Es11_d1.png", "png");
    
    h2->SetFillColor(kBlue + 1);
    h2->Draw();
    gStyle->SetOptFit(kTRUE);
    c->Print("Es11_d2.png", "png");
    
    h3->SetFillColor(kBlue + 1);
    h3->Draw();
    gStyle->SetOptFit(kTRUE);
    c->Print("Es11_d3.png", "png");
    
    delete h1;
    delete h2;
    delete h3;
    delete d1;
    delete d2;
    delete d3;
    delete c;
    

    return 0;
}
