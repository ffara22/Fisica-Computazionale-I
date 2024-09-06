/*
c++ -o Esercizio5TS `root-config --glibs --cflags` Esercizio5TS.cpp
*/

//--- Approssimazione ---
//Entrambe le funzioni di calcolo arrivo fino a una soglia di underflow del delta intorno a e^-25 = e-10, giustificata dalla dimensione della memoria usata (double), la differenza è che il metodo Simspon arriva prima a tale soglia con il quadrato della velocità del primo

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "quadratore.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TF1.h"


double integrando(double x) {
    return x*x + x*sin(4*x);
}

//--- Tutto il codice serve a graficare i risultati ---

int main(int argc, char const *argv[]) {
    
    TGraph* g_T = new TGraph;
    TGraph* g_S = new TGraph;
    
    double ris = 1./16.*(2736 - 4*cos(4) - 32*cos(32) + sin(4) + sin(32));
    
    for (int i = 3; i < 10000000; i = 3*i){
        double m = 1./i;
        g_T->SetPoint(g_T->GetN(), log(m), log(Trapezio(integrando, -1, 8, i) - ris));
        g_S->SetPoint(g_T->GetN(), log(m), log(fabs(Simpson(integrando, -1, 8, i) - ris)));
    }
    
    TCanvas* c = new TCanvas();
    
    g_T->SetMarkerStyle(20);
    g_T->SetMarkerColor(kRed + 1);
    g_T->SetMarkerSize(1);
    g_T->GetHistogram()->GetXaxis()->SetTitle("log(1/N)");
    g_T->GetHistogram()->GetYaxis()->SetTitle("log(#delta)");
    g_T->GetHistogram()->GetYaxis()->SetRangeUser(-28, 8);
    g_T->Draw("AP");
    
    g_S->SetMarkerStyle(20);
    g_S->SetMarkerColor(kGreen + 1);
    g_S->SetMarkerSize(1);
    g_S->Draw("P, same");
    
    c->SetGrid();
    c->Print("Es5_EvoluzioneTS.png", "png");
    
    delete g_T;
    delete g_S;
    delete c;
    
    return 0;
}
