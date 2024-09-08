#ifndef casual_h
#define casual_h

double TrialBernoulli(double neg, double pos) {
    if (rand()%2 == 0) {
        return pos;
    } else {
        return neg;
    }
}

double RandIntervallo(double min, double max) {
  return min + (max - min)*rand()/static_cast<double>(RAND_MAX);
}

double RandTCLUniforme(double min, double max, int N) {
  double y = .0;
  for(int i = 0; i < N ; i++){
    y += RandIntervallo(min, max);
  }
  return y/N;
}

double RandTCLBernulli(double neg, double pos, int N) {
  double y = .0;
  for(int i = 0; i < N ; i++){
    y += TrialBernoulli(neg, pos);
  }
  return y/N;
}

double RandMFI(double InvComulativa(double), double y1, double y2) {
    double y = RandIntervallo(y1, y2);
    return InvComulativa(y);
}


#endif

