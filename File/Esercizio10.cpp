/*
c++ -o Esercizio10 `root-config --glibs --cflags` Esercizio10.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>

#include "TGraph.h"
#include "TH1F.h"
#include "TCanvas.h"

#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

using namespace std;


double f1(double x) {
    return pow(x, 7)*exp(-x);
}
double f2(double x) {
    return (exp(x) + exp(-x))/2.;
}

double f3(double x) {
    return x*x + x*sin(4*x);
}




double RandIntervallo(double min, double max){
  return min + (max - min)*rand()/static_cast<double>(RAND_MAX);
}

double CrudeMontecarlo(double f(double), double a, double b, int Nmax) {
    double sum = 0;

    for (int k = 0; k < Nmax; k++) {
        sum += f(RandIntervallo(a, b));
    }
    
    return (b - a)*sum/Nmax;
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




double errore(double* x, double* par) {
    return par[0]*pow(x[0], par[1]);
}

int main(int argc, char const *argv[]) {
        
    if (argc < 2) {
        cout << "Inserire Nmax: " << endl;
        exit(1);
    }
    
    int Nmax = atoi(argv[1]);
    
    double res1 = 5040 - 648240/exp(5);
    double res2 = 0.5*(exp(8) - exp(-8) - exp(3) + exp(-3));
    double res3 = 1/16.*(2736 + sin(4) + sin(32) - 4.*cos(4) - 32.*cos(32));
    
//    --- Calcolo diretto con i metodi e riempimento dei grafici ---
    
    TGraph * g11 = new TGraph;
    TGraph * g12 = new TGraph;
    TGraph * g21 = new TGraph;
    TGraph * g22 = new TGraph;
    TGraph * g31 = new TGraph;
    TGraph * g32 = new TGraph;
    
    for (int n = 10; n < Nmax; n *= 1.25) {
        
        g11->SetPoint(g11->GetN(), n, fabs(res1 - CrudeMontecarlo(f1, 0, 5, n)));
        g12->SetPoint(g12->GetN(), n, fabs(res1 - HOM(f1, 751, 0, 5, n)));
        
        g21->SetPoint(g21->GetN(), n ,fabs(res2 - CrudeMontecarlo(f2, 3, 8, n)));
        g22->SetPoint(g22->GetN(), n, fabs(res2 - HOM(f2, f2(8), 3, 8, n)));
        
        g31->SetPoint(g31->GetN(), n, fabs(res3 - CrudeMontecarlo(f3, -1, 8, n)));
        g32->SetPoint(g32->GetN(), n, fabs(res3 - HOM(f3, f3(8), -1, 8, n)));
    }
    
//    --- Stima finale ---
    cout << "E3 con Montecarlo: " << setprecision(16) << CrudeMontecarlo(f1, 0, 5, Nmax) << endl;
    cout << "E3 con HOM: " << setprecision(16) << HOM(f1, 751, 0, 5, Nmax) << endl;
    
    cout << "E4 con Montecarlo: " << setprecision(16) << CrudeMontecarlo(f2, 3, 8, Nmax) << endl;
    cout << "E4 con HOM: " << setprecision(16) << HOM(f2, f2(8), 3, 8, Nmax) << endl;
    
    cout << "E5 con Montecarlo: " << setprecision(16) << CrudeMontecarlo(f3, -1, 8, Nmax) << endl;
    cout << "E5 con HOM: " << setprecision(16) << HOM(f3, f3(8), -1, 8, Nmax) << endl;
    
//    --- Fit per verifica dei parametri di dipendenza dei risultati ---
        
    TF1* f_fit1 = new TF1("f_fit1", errore, 0., 10000000, 2);
    f_fit1->SetParameter(0, 100);
    f_fit1->SetParameter(1, -0.5);
    f_fit1->SetParName(0, "#sigma");
    f_fit1->SetParName(1, "esponente");
    TFitResultPtr fit_ris1 = g11->Fit(f_fit1, "S");
    if(fit_ris1->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    TF1* f_fit2 = new TF1("f_fit2", errore, 0., 10000000, 2);
    f_fit2->SetParameter(0, 100);
    f_fit2->SetParameter(1, -0.5);
    f_fit2->SetParName(0, "#sigma");
    f_fit2->SetParName(1, "esponente");
    TFitResultPtr fit_ris2 = g21->Fit(f_fit2, "S");
    if(fit_ris2->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    TF1* f_fit3 = new TF1("f_fit3", errore, 0., 10000000, 2);
    f_fit3->SetParameter(0, 100);
    f_fit3->SetParameter(1, -0.5);
    f_fit3->SetParName(0, "#sigma");
    f_fit3->SetParName(1, "esponente");
    TFitResultPtr fit_ris3 = g31->Fit(f_fit1, "S");
    if(fit_ris3->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
//    --- Graficazione dei risultati ---
    
    TCanvas * c = new TCanvas;
    
    g11->SetMarkerStyle(20);
    g11->SetMarkerColor(kBlue + 1);
    g11->SetMarkerSize(0.5);
    g11->GetHistogram()->GetXaxis()->SetTitle("n");
    g11->GetHistogram()->GetYaxis()->SetTitle("#Delta");
    g11->Draw("ACP");
    
    g12->SetMarkerStyle(20);
    g12->SetMarkerColor(kRed + 1);
    g12->SetMarkerSize(0.5);
    g12->Draw("CP, same");
     
    gStyle->SetOptFit(kTRUE);
    gStyle->SetOptFit(gStyle->GetOptFit() |  1<<5);
    
    c->SetGrid();
    c->SetLogx();
    c->SetLogy();
    c->Print("Es10_f1.png", "png");
                                  
    
    g21->SetMarkerStyle(20);
    g21->SetMarkerColor(kBlue + 1);
    g21->SetMarkerSize(0.5);
    g21->GetHistogram()->GetXaxis()->SetTitle("n");
    g21->GetHistogram()->GetYaxis()->SetTitle("#Delta");
    g21->Draw("ACP");

    g22->SetMarkerStyle(20);
    g22->SetMarkerColor(kRed + 1);
    g22->SetMarkerSize(0.5);
    g22->Draw("CP, same");
    
    gStyle->SetOptFit(kTRUE);
    gStyle->SetOptFit(gStyle->GetOptFit() |  1<<5);

    c->SetGrid();
    c->SetLogx();
    c->SetLogy();
    c->Print("Es10_f2.png", "png");
    
    
    g31->SetMarkerStyle(20);
    g31->SetMarkerColor(kBlue + 1);
    g31->SetMarkerSize(0.5);
    g31->GetHistogram()->GetXaxis()->SetTitle("n");
    g31->GetHistogram()->GetYaxis()->SetTitle("#Delta");
    g31->Draw("ACP");

    g32->SetMarkerStyle(20);
    g32->SetMarkerColor(kRed + 1);
    g32->SetMarkerSize(0.5);
    g32->Draw("CP, same");
    
    gStyle->SetOptFit(kTRUE);
    gStyle->SetOptFit(gStyle->GetOptFit() |  1<<5);

    c->SetGrid();
    c->SetLogx();
    c->SetLogy();
    c->Print("Es10_f3.png", "png");
    

    return 0;
}
