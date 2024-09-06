/*
c++ -o Esercizio1 `root-config --glibs --cflags` Esercizio1.cpp
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"

#define pi 3.141592653589793238462643383279502884197169399375105820974944

using namespace std;

using T = float;

//--- Arrotondameto ---
//Le due somme lavorano in modo diverso: la prima parte da 1 (cifra significativa dominante) per cui a un certo momento somma costantemente zeri(zeri nel senso di relativi alla cifra dominante); la somma inversa invece conserva il più possibile le cifre significative, sommando volta per volta cifre "comparabili". Il "plateau" dipende dalla cifra limite float: 8byte rappresentano in virgola mobile un numero di circa 1e-7: n limite è quindi la radice di 1e7 che si riscontra in circa  3-4e3 n. Graficando il float è stato possibile verificarlo facilmente essendo il numero di operazioni non estreme, successivamente si è scritto il codice di modo da diminuire le operazione mettendo nel grafico solo determinati punti; replichiamo il ragionamento per i double: 16byte rappresentano in virgola mobile un numero di circa 1e-16: n limite è quindi dell'ordine di 1e8

int main(int argc, char const *argv[]) {
    
    if (argc < 2) {
        cout << "Inserire numero di punti" << endl;
        exit(1);
    }
    
    long int N = atoi(argv[1]);
    
    T ris = (pi*pi)/6.;

    
//    --- Somma Diretta ---
    
    T sum_dir = 0;
    TGraph* g_dir = new TGraph;
    
    for (long int i = 1; i < N + 1; i++) {
        sum_dir += 1./(i*i);
        
        if (fmod(log2(i), 1) == 0) {
            g_dir->SetPoint(g_dir->GetN(), i, abs(sum_dir - ris));
        }
    }
    
    cout << "Fine calcolo sommatoria diretta" << endl;
    
//    --- Somma Inversa ---
    
    TGraph* g_inv = new TGraph;
    
    for (long int j = 1; j < N + 1; j=j*2) {
        T sum_inv = 0;
        for (long int i = j; i > 0; i = i - 1) {
            sum_inv += 1./(i*i);
        }
        
        g_inv->SetPoint(g_inv->GetN(), j, abs(sum_inv - ris));
        
    }
    
    cout << "Fine calcolo sommatoria inversa" << endl;
    
    
//    --- Graficazione dei risultati ---
    
    TCanvas* c = new TCanvas();
    
    g_dir->SetMarkerStyle(20);
    g_dir->SetMarkerColor(kBlue + 1);
    g_dir->SetMarkerSize(1);
    g_dir->GetHistogram()->GetXaxis()->SetTitle("N");
    g_dir->GetHistogram()->GetYaxis()->SetTitle("#Delta");
    g_dir->GetHistogram()->GetXaxis()->SetRangeUser(1, N);
    g_dir->GetHistogram()->GetYaxis()->SetRangeUser(0.000000000001, 1);
    g_dir->Draw("AP");
    
    g_inv->SetMarkerStyle(20);
    g_inv->SetMarkerColor(kRed + 1);
    g_inv->SetMarkerSize(0.5);
    g_inv->Draw("P, same");
    
    c->SetLogx();
    c->SetLogy();
    c->SetGrid();
    c->Print("Es1_Delta.png", "png");
    
    delete g_dir;
    delete g_inv;
    delete c;
    
    return 0;
}

