/*
c++ -o Esercizio14 `root-config --glibs --cflags` Esercizio14.cpp
*/

// La struttura è la seguente: una libreria prende in input dimensione del problema, set di funzioni che definiscono il problema, numeri di passi, tempo iniziale e tempo finale, e una stringa per identificare il metodo. Le funzioni sono in generale dipendenti da N variabili sintetizzate nel vettore v, in y vettore sono immagazzinate le condizioni iniziali

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"

#include "integratore.h"

#define N 2

//--- Condizionamento ---
//L'oscillatore armonico è un problema intrinsecamente ben condizionato

//--- Stabilità ---
//E' evidente che il metodo di RK4 sia in assoluto il più stabile: sebbene si ottengano gia buoni risultati con RK2, la differenza sostanziale avviene con eulero che per convergere ha bisogno di passi molto piccoli e tempi non troppo grandi.

using namespace std;

double f0(double t, double *v)
{
  return v[1];
}

double f1(double t, double *v)
{
  return -v[0];
}




double f_sol(double t){
    return sin(t);
}


int main(int argc, char *argv[]) {
    
    double y[N], t_i, t_f;
    
    double (*f[N])(double t, double *v)={f0,f1};
    
//    --- Setting dei dati del problema ---
    
    t_i = 0.;
    t_f = 5.;
    
    
//    --- Eulero ---
    
    char* Eulero = "Eulero";
    TGraph* g1 = new TGraph;
    
    for (int tp = 1; tp < pow(2, 20); tp = tp*2) {
        
        y[0] = 0.;
        y[1] = 1.;
        
        integratore(N, y, f, t_i, t_f, tp, Eulero);
        
        double deltaE = abs(f_sol(t_f) - y[0]);
        
        g1->SetPoint(g1->GetN(), log((t_f - t_i)/tp), log(deltaE));
        
    }
    
//    --- RK2 ---
    
    char* RK2 = "RK2";
    TGraph* g2 = new TGraph;
    
    for (int tp = 1; tp < pow(2, 20); tp = tp*2) {
        
        y[0] = 0.;
        y[1] = 1.;
        
        integratore(N, y, f, t_i, t_f, tp, RK2);
        
        double deltaRK2 = abs(f_sol(t_f) - y[0]);
        
        g2->SetPoint(g2->GetN(), log((t_f - t_i)/tp), log(deltaRK2));
        
    }
        
//    --- RK4 ---
    
    char* RK4 = "RK4";
    TGraph* g3 = new TGraph;
    
    for (int tp = 1; tp < pow(2, 20); tp = tp*2) {
        
        y[0] = 0.;
        y[1] = 1.;
        
        integratore(N, y, f, t_i, t_f, tp, RK4);
        
        double deltaRK4 = abs(f_sol(t_f) - y[0]);
        
        g3->SetPoint(g3->GetN(), log((t_f - t_i)/tp), log(deltaRK4));
        
    }
    
//    --- Graficazione dei risultati ---
    
    TCanvas* c = new TCanvas;
    
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kRed + 1);
    g1->SetMarkerSize(1);
    g1->GetHistogram()->GetYaxis()->SetRangeUser(-40., 5.);
    g1->GetHistogram()->GetXaxis()->SetRangeUser(-15., 3.);
    g1->GetHistogram()->GetXaxis()->SetTitle("log(h)");
    g1->GetHistogram()->GetYaxis()->SetTitle("log(#delta)");
    g1->Draw("AP");
    
    g2->SetMarkerStyle(20);
    g2->SetMarkerColor(kGreen + 1);
    g2->SetMarkerSize(1);
    g2->Draw("P");
    
    g3->SetMarkerStyle(20);
    g3->SetMarkerColor(kBlue + 1);
    g3->SetMarkerSize(1);
    g3->Draw("P");
    
    c->SetGrid();
    c->Print("Es14_Delta.png", "png");
    
    delete g1;
    delete g2;
    delete g3;
    delete c;
    
    return 0;
}
