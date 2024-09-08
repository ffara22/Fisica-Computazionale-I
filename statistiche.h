#ifndef statistiche_h
#define statistiche_h

#include <cmath>
#include <vector>

// --- Momenti ---

template <class T>
double Media(std::vector<T> &inputV){
    double somma = 0;
    for (int i = 0; i < inputV.size(); i++){
        somma += inputV.at(i);
    }
    return somma/inputV.size();
}

template <class T>
double M2(std::vector<T> &inputV) {
    double sommaq = 0;
    for (int i = 0; i < inputV.size(); i++)
    {
        sommaq += inputV.at(i)*inputV.at(i);
    }
    return sommaq/inputV.size();
}

template <class T>
double M3(std::vector<T> &inputV) {
    double somma = 0;
    for (int i = 0; i < inputV.size(); i++)
    {
        somma += pow(inputV.at(i), 3);
    }
    return somma/inputV.size();
}


template <class T>
double M4(std::vector<T> &inputV) {
    double somma = 0;
    for (int i = 0; i < inputV.size(); i++)
    {
        somma += pow(inputV.at(i), 4);
    }
    return somma/inputV.size();
}


template <class T>
double M6(std::vector<T> &inputV) {
    double somma = 0;
    for (int i = 0; i < inputV.size(); i++)
    {
        somma += pow(inputV.at(i), 6);
    }
    return somma/inputV.size();
}

// --- Altri stimatori ---

template <class T>
double Varianza(std::vector<T> &inputV) {
    double somma = Media(inputV);
    double sommaq = M2(inputV);
    return sommaq - somma*somma;
}

template <class T>
double Sigma(std::vector<T> &inputV) {
    return sqrt(Varianza(inputV));
}

template <class T>
double Mediana(std::vector<T> &inputV) {
  sort(inputV.begin(), inputV.end());
  if (inputV.size() / 2 == 0){
    return 0.5*(inputV.at(inputV.size()/2 - 1) + inputV.at(inputV.size()/2));
  }
  return inputV.at(inputV.size()/2);
}


// --- Momenti centrali ---

template <class T>
double Skewness(std::vector<T> &inputV) {
    double beta1 = 0;
    double media = Media(inputV);
    for (int i = 0; i < inputV.size(); i++)
    {
        beta1 += pow((inputV.at(i) - media),3);
    }
    return beta1/(inputV.size()*Sigma(inputV)*Sigma(inputV)*Sigma(inputV));
}


template <class T>
double Curtosi(std::vector<T> &inputV) {
    double beta2  = 0;
    double media = Media(inputV);
    for (int i = 0; i < inputV.size(); i++)
    {
        beta2 += pow((inputV.at(i)- media), 4);
    }
    return beta2/(inputV.size()*Varianza(inputV)*Varianza(inputV)) - 3.;
}




#endif
