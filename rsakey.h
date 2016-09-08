#ifndef RSAKEY_H
#define RSAKEY_H

typedef struct {
  int value;
  int n;
} RsaKey;

int extendedEuclid(int dividend, int divisor, int y[]);
void selectE(int eulersTotientOfN, int *e, int maxKeys);
int calculateD(int inverseE, int eulerTotientOfN);
int calculateN(int p, int q);
int calculateEulerTotient(int p, int q);

#endif