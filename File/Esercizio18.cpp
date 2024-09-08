/*
c++ -o Esercizio18 `root-config --glibs --cflags` Esercizio18.cpp
*/

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"

#include "integratore.h"

#define N 18

//--- Condizionamento ---
//Il problema a tre corpi è intrinsecamente mal condizionato
//
//--- Stabilità ---
//Per garantire una buona stabilità è necessario ricorrere principalmente al metodo RK4

// Metto in define i valori delle masse e poi le varierò a seconda dal problema in esame. Il vettore è ordinato in modo (x1,y1,z1,x2,y2,z2,x3,y3,z3,vx1,vy1,vz1,vx2,vy2,vz2,vx3,vy3,vz3).

#define m1 1.6
#define m2 0.4
#define m3 0.4

using namespace std;

double x1(double t, double *v) {
    return v[9];
}

double y1(double t, double *v) {
    return v[10];
}

double z1(double t, double *v) {
    return v[11];
}

double x2(double t, double *v) {
    return v[12];
}

double y2(double t, double *v) {
    return v[13];
}

double z2(double t, double *v) {
    return v[14];
}

double x3(double t, double *v) {
    return v[15];
}

double y3(double t, double *v) {
    return v[16];
}

double z3(double t, double *v) {
    return v[17];
}


double vx1(double t, double *v) {
    return
        - m2*(v[0] - v[3])
        /pow(pow(v[0] - v[3], 2) + pow(v[1] - v[4], 2) + pow(v[2] - v[5], 2), 3./2.)
        - m3*(v[0] - v[6])
        /pow(pow(v[0] - v[6], 2) + pow(v[1] - v[7], 2) + pow(v[2] - v[8], 2), 3./2.);
}

double vy1(double t, double *v) {
    return 
        - m2*(v[1] - v[4])
        /pow(pow(v[0] - v[3], 2) + pow(v[1] - v[4], 2) + pow(v[2] - v[5], 2), 3./2.)
        - m3*(v[1] - v[7])
        /pow(pow(v[0] - v[6], 2) + pow(v[1] - v[7], 2) + pow(v[2] - v[8], 2), 3./2.);
}

double vz1(double t, double *v) {
    return 
        - m2*(v[2] - v[5])
        /pow(pow(v[0] - v[3], 2) + pow(v[1] - v[4], 2) + pow(v[2] - v[5], 2), 3./2.)
        - m3*(v[2] - v[8])
        /pow(pow(v[0] - v[6], 2) + pow(v[1] - v[7], 2) + pow(v[2] - v[8], 2), 3./2.);
}

double vx2(double t, double *v) {
    return 
        - m1*(v[3] - v[0])
        /pow(pow(v[0] - v[3], 2) + pow(v[1] - v[4], 2) + pow(v[2] - v[5], 2), 3./2.)
        - m3*(v[3] - v[6])
        /pow(pow(v[3] - v[6], 2) + pow(v[4] - v[7], 2) + pow(v[5] - v[8], 2), 3./2.);
}

double vy2(double t, double *v) {
    return 
        - m1*(v[4] - v[1])
        /pow(pow(v[0] - v[3], 2) + pow(v[1] - v[4], 2) + pow(v[2] - v[5], 2), 3./2.)
        - m3*(v[4] - v[7])
        /pow(pow(v[3] - v[6], 2) + pow(v[4] - v[7], 2) + pow(v[5] - v[8], 2), 3./2.);
}

double vz2(double t, double *v) {
    return 
        - m1*(v[5] - v[2])
        /pow(pow(v[0] - v[3], 2) + pow(v[1] - v[4], 2) + pow(v[2] - v[5], 2), 3./2.)
        - m3*(v[5] - v[8])
        /pow(pow(v[3] - v[6], 2) + pow(v[4] - v[7], 2) + pow(v[5] - v[8], 2), 3/2.);
}

double vx3(double t, double *v) {
    return 
        - m2*(v[6] - v[3])
        /pow(pow(v[3] - v[6], 2) + pow(v[4] - v[7], 2) + pow(v[5] - v[8], 2), 3./2.)
        - m1*(v[6] - v[0])
        /pow(pow(v[0] - v[6], 2) + pow(v[1] - v[7], 2) + pow(v[2] - v[8], 2), 3./2.);
}

double vy3(double t, double *v) {
    return
        - m2*(v[7] - v[4])
        /pow(pow(v[3] - v[6], 2) + pow(v[4] - v[7], 2) + pow(v[5] - v[8], 2), 3./2.)
        - m1*(v[7] - v[1])
        /pow(pow(v[0] - v[6], 2) + pow(v[1] - v[7], 2) + pow(v[2] - v[8], 2), 3./2.);
}

double vz3(double t, double *v) {
    return
        - m2*(v[8] - v[5])
        /pow(pow(v[3] - v[6], 2) + pow(v[4] - v[7], 2) + pow(v[5] - v[8], 2), 3./2.)
        - m1*(v[8] - v[2])
        /pow(pow(v[0] - v[6], 2) + pow(v[1] - v[7], 2) + pow(v[2] - v[8], 2), 3./2.);
}

int main(int argc, char *argv[]) {
    
    double h, w[N], t_passo, t_i, t_f;
    
    double (*f[N])(double t, double *v)={x1,y1,z1,x2,y2,z2,x3,y3,z3,vx1,vy1,vz1,vx2,vy2,vz2,vx3,vy3,vz3};
    
//    --- Setting dei dati del problema ---
    
    w[0] = 1.;
    w[1] = 0.;
    w[2] = 0.;
    
    w[3] = -1.;
    w[4] = 0.;
    w[5] = 0.;
    
    w[6] = 0.;
    w[7] = 0.;
    w[8] = 0.;
    
    w[9] = 0.;
    w[10] = 0.4;
    w[11] = 0.;
    
    w[12] = 0.;
    w[13] = -0.8;
    w[14] = 0.7;
    
    w[15] = 0.;
    w[16] = -0.8;
    w[17] = -0.7;
    
    t_passo = 100000.;
    t_i = 0.;
    t_f = 100.;
    
    h = (t_f - t_i)/t_passo;
    
    TGraph* g = new TGraph; //Grafico dell'energia
    
    for (int n = 0; n < t_passo; n++) {
        
        integratore(N, w, f, n*h, (n+1)*h, 1, argv[1]);
        
        double T = 0.5*m1*(w[9]*w[9] + w[10]*w[10] + w[11]*w[11]) + 0.5*m2*(w[12]*w[12] + w[13]*w[13] + w[14]*w[14]) + 0.5*m3*(w[15]*w[15] + w[16]*w[16] + w[17]*w[17]);
        double U = -0.5*(m1*m2/sqrt(pow(w[0] - w[3], 2) + pow(w[1] - w[4], 2) + pow(w[2] - w[5], 2)) + m2*m3/sqrt(pow(w[3] - w[6], 2) + pow(w[4] - w[7], 2) + pow(w[5] - w[8], 2)) + m3*m1/sqrt(pow(w[0] - w[6], 2) + pow(w[1] - w[7], 2) + pow(w[2] - w[8], 2)));
                
        g->SetPoint(g->GetN(), (n+1)*h, T + U);
    }
    
//    --- Graficazione energia ---
    
    TCanvas* c = new TCanvas;
    
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kBlue + 1);
    g->SetMarkerSize(0.3);
    g->GetHistogram()->GetXaxis()->SetTitle("t");
    g->GetHistogram()->GetYaxis()->SetTitle("E");
    g->Draw("AP");
    
    c->SetGrid();
    c->Print("Es18_EnergiaII.png", "png");
    
    delete c;
    delete g;
    
    return 0;
}

