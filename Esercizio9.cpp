/*
c++ -o Esercizio9 `root-config --glibs --cflags` Esercizio9.cpp
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

using namespace std;

int main(int argc, char const *argv[]){
    
    if (argc < 2) {
        cout << "Inserire Nmax" << endl;
        exit(0);
    }
    
    double xMin = -1.;
    double xMax = 1.;
    int Nmax = atoi(argv[1]);
    int M = 10000;
    
    vector <double> data;
    TH1F * h = new TH1F("Le ultime due sono state stimate dal fit", "", 100, - 0.6, 0.6);
    TGraph * g_mean = new TGraph;
    TGraph * g_M3 = new TGraph;
    TGraph * g_M4 = new TGraph;
    TGraph * g_M2 = new TGraph;
    TGraph * g_r1 = new TGraph;
    TGraph * g_r2 = new TGraph;
    
    for (int i = 1; i < Nmax; i++) {
        
        data.clear();
        
        for (int j = 0; j < M; j++) {
            
            double var = RandTCLUniforme(xMin, xMax, i);
//            double var = RandTCLBernulli(xMin, xMax, i);
            
            data.push_back(var);
        }
        
        g_mean->SetPoint(g_mean->GetN(), i, Media(data));
        g_M3->SetPoint(g_M3->GetN(), i, M3(data));
        g_M4->SetPoint(g_M4->GetN(), i, M4(data));
        g_M2->SetPoint(g_M2->GetN(), i, M2(data));
        
        g_r1->SetPoint(g_r1->GetN(), i, M4(data)/pow(M2(data), 2));
        g_r2->SetPoint(g_r2->GetN(), i, M6(data)/(M4(data)*M2(data)));
    }
    
    //    Metto dentro all'istogramma gli ultimi dati generati
    for (int i = 0; i < data.size(); i++) {
        h->Fill(data.at(i));
    }
    
    
    //    --- Fit Gaussiano ---
    
    TF1 f_fit ("f_fit", "gaus(0)", xMin, xMax);
    f_fit.SetParameter(1, Media(data));
    f_fit.SetParameter(2, Sigma(data));
    TFitResultPtr fit_result = h->Fit(&f_fit, "S+");
    if(fit_result->IsValid() == true){
        cout << "Il fit è avvenuto con successo \n" << endl;
    }
    
    
    //    --- Graficazione dei risultati ---
    
    TCanvas * c = new TCanvas();
    
    h->Draw();
    h->SetFillColor(kBlue +1);
    
    gStyle->SetOptFit(kTRUE);
    c->Print("Es9_TCLU.png", "png");
    
    
    
    g_mean->SetMarkerStyle(20);
    g_mean->SetMarkerColor(kBlue + 1);
    g_mean->SetMarkerSize(0.5);
//    g_mean->GetHistogram()->SetTitle("Blu: mean  Violet: M2   Red: M3   Green:M4");
    g_mean->GetHistogram()->GetYaxis()->SetRangeUser(- 0.1, 0.1);
    g_mean->GetHistogram()->GetXaxis()->SetTitle("N");
    g_mean->Draw("AP");
    
    g_M3->SetMarkerStyle(20);
    g_M3->SetMarkerColor(kRed + 1);
    g_M3->SetMarkerSize(0.4);
    g_M3->Draw("P, same");
    
    g_M4->SetMarkerStyle(20);
    g_M4->SetMarkerColor(kGreen + 1);
    g_M4->SetMarkerSize(0.5);
    g_M4->Draw("P, same");
    
    g_M2->SetMarkerStyle(20);
    g_M2->SetMarkerColor(kViolet + 1);
    g_M2->SetMarkerSize(0.5);
    g_M2->Draw("P, same");
    
    c->SetGrid();
    c->Print("Es9_TCLUpar.png", "png");
    
    
    
    g_r1->SetMarkerStyle(20);
    g_r1->SetMarkerColor(kBlue + 1);
    g_r1->SetMarkerSize(0.5);
//    g_r1->GetHistogram()->SetTitle("Blu: M4/M2, Red: M6/M4*M2");
    g_r1->GetHistogram()->GetYaxis()->SetRangeUser(2.0, 6.0);
    g_r1->GetHistogram()->GetXaxis()->SetTitle("N");
    g_r1->Draw("AP");
    
    g_r2->SetMarkerStyle(20);
    g_r2->SetMarkerColor(kRed + 1);
    g_r2->SetMarkerSize(0.5);
    g_r2->Draw("P, same");
    
    c->SetGrid();
    c->Print("Es9_TCLUpar2.png", "png");

    delete c;
    delete h;
                       
    delete g_mean;
    delete g_M3;
    delete g_M4;
    delete g_M2;
                       
    delete g_r1;
    delete g_r2;
    
    return 0;
    
}
