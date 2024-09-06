#ifndef integratore_h
#define integratore_h

#include <fstream>
#include <cmath>
#include <string>



//  --- Funzione di stampa ---
void stampa(int N, double t, double *v, FILE *output)
{
  fprintf(output, "%1.16lf ",t);
  for(int n = 0; n < N; n++) fprintf(output, "%1.16lf ", v[n]);
  fprintf(output, "\n");
}

//  --- Definizione del passo elementare di integrazione ---

void Eulero(int N, double t, double *v, double h, double (*pf[N])(double t, double *v))
{
  double k1[N];

  for(int n=0;n<N;n++) k1[n] = h * pf[n](t,v);

  for(int n=0;n<N;n++) v[n] = v[n] + k1[n];
  
  return;
}
  

void RK2(int N, double t, double *v, double h, double (*pf[N])(double t, double *v))
{
  double k1[N], k2[N], v_tmp[N];

  for(int n=0;n<N;n++) k1[n] = h * pf[n](t,v);

  for(int n=0;n<N;n++) v_tmp[n] = v[n] + k1[n] / 2.0;
  for(int n=0;n<N;n++) k2[n] = h * pf[n](t+h/2.,v_tmp);

  for(int n=0;n<N;n++) v[n] = v[n] + k2[n];
  
  return;
}
  

void RK4(int N, double t, double *v, double h, double (*pf[N])(double t, double *v))
{
  double k1[N], k2[N], k3[N], k4[N], v_tmp[N];

  for(int n=0;n<N;n++) k1[n] = h * pf[n](t,v);

  for(int n=0;n<N;n++) v_tmp[n] = v[n] + k1[n] / 2.0;
  for(int n=0;n<N;n++) k2[n] = h * pf[n](t+h/2.,v_tmp);

  for(int n=0;n<N;n++) v_tmp[n] = v[n] + k2[n] / 2.0;
  for(int n=0;n<N;n++) k3[n] = h * pf[n](t+h/2.,v_tmp);
 
  for(int n=0;n<N;n++) v_tmp[n] = v[n] + k3[n];
  for(int n=0;n<N;n++) k4[n] = h * pf[n](t+h,v_tmp);

  for(int n=0;n<N;n++) v[n] = v[n] + (k1[n] + 2. * k2[n] + 2. * k3[n] + k4[n])/6.;
  
  return;
}

//  --- Definizione dell'integratore ---

void integratore(int N, double y[N], double (*pf[N])(double t, double *v), double t_i, double t_f, int t_steps, char metodo[])
{
    void (*step)(int N, double t, double *v, double h, double (*pf[N])(double t, double *v));
    double t = t_i;
    double h = (t_f - t_i)/t_steps ;
    
    FILE *output = fopen((std::string(metodo) + ".txt").c_str(), "a");
    
    //  --- Scelta del Metodo ---
    if(strcmp(metodo, "Eulero") == 0) {
        step = Eulero;
    } else if (strcmp(metodo, "RK2") == 0) {
        step = RK2;
    }  else if (strcmp(metodo, "RK4") == 0) {
        step = RK4;
    }  else printf("metodo %s non esiste!\n",metodo);
    
    //  --- Evoluzione ---
    for(int k=0; k < t_steps; k++)
    {
        step(N, t, y, h, pf);
        t = t + h;
        stampa(N, t, y, output);
    }
    
    fclose(output);
    
    return;
}

#endif

