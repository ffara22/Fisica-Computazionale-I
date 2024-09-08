/*
c++ -o Esercizio2 `root-config --glibs --cflags` Esercizio2.cpp
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"

#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

using namespace std;

using T = float;

// Funzione per il fit dei risultati
double esponenziale(double* x,double* par){
  return par[0]*exp(par[1]*x[0]);
}

//--- Arrotondameto ---
//Chi = Phi1 + εPhi2 per azione del troncamento alla cifra decimale della precisione; di che ordine è epsilon? Chiaramente deve essere sotto il float lavorando a quella precisione, ci aspettiamo un epsilon dell'ordine e8.


int main(int argc, char const *argv[]) {
    
//      --- Controllo preliminare ---
    if (argc < 2) {
        cout << "Inserire argomento" << endl;
        exit(1);
    }
    
    int Nmax = atoi(argv[1]);
    
    
    T phi1 = (sqrt(5.) - 1.)/2.;
    T phi2 = -(sqrt(5.) + 1.)/2.;
    
    TGraph* g_pow = new TGraph;
    TGraph* g_del = new TGraph;
    
    
//    --- Metodo ricorsivo e calcolo del delta ---
    
    T chi_nmeno1 = 1.;
    T chi_n = phi1;
    T chi_npiu1 = 0.;
    
    g_pow->SetPoint(g_pow->GetN(), 0, chi_nmeno1);
    g_del->SetPoint(g_del->GetN(), 0, 0.);
    
    g_pow->SetPoint(g_pow->GetN(), 1, chi_n);
    g_del->SetPoint(g_del->GetN(), 0, fabs(phi1 - phi1));
    
    for (int i = 2; i < Nmax; i++) {
        chi_npiu1 = chi_nmeno1 - chi_n;
        chi_nmeno1 = chi_n;
        chi_n = chi_npiu1;
        
        g_pow->SetPoint(g_pow->GetN(), i, chi_npiu1);
        g_del->SetPoint(g_del->GetN(), i, fabs(pow(phi1, i) - chi_npiu1));
    }
    
    
    
//    --- Fit per verifica dei parametri di dipendenza dei risultati ---
    
    TF1* f_fit = new TF1("f_fit", esponenziale, 30., 80., 2);
    f_fit->SetParameter(0, 0.0000000000000001);
    f_fit->SetParameter(1, 0.4812);
    f_fit->SetParName(0, "#epsilon");
    f_fit->SetParName(1, "log(|#phi2|)");
    TFitResultPtr fit_ris = g_del->Fit(f_fit, "S");
    if(fit_ris->IsValid() == true){
      cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    cout << setprecision(34) << "Modulo di phi2: " << exp(fit_ris->Parameter(1)) << endl;
    
    
                    
//    --- Graficazione dei risultati ---
    
    TCanvas* c = new TCanvas();
                    
    g_pow->SetMarkerStyle(20);
    g_pow->SetMarkerColor(kBlue + 1);
    g_pow->SetMarkerSize(0.5);
    g_pow->GetHistogram()->GetYaxis()->SetRangeUser(0., 1000000.);
    g_pow->GetHistogram()->GetXaxis()->SetTitle("N");
    g_pow->GetHistogram()->GetYaxis()->SetTitle("Potenza n-esima e #Delta");
    g_pow->Draw("AP");
    
    g_del->SetMarkerStyle(4);
    g_del->SetMarkerColor(kGreen + 1);
    g_del->SetMarkerSize(1);
    g_del->Draw("P, same");
    
    gStyle->SetOptFit(kTRUE);
    
    c->SetLogy();
    c->SetGrid();
    c->Print("Es2_PotenzaN.png", "png");
    
    delete g_del;
    delete g_pow;
    delete c;
    
    return 0;
}
