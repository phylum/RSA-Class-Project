#include "rsakey.h"

int extendedEuclid(int dividend, int divisor, int y[]) {
  if(divisor > dividend) {
    swap(&divisor, &dividend);
  }
  
  if(divisor == 0) {
    return dividend;
  }
  else {
    int quotient;
    quotient = dividend / divisor;
    
    int nextY;
    nextY = y[0] - quotient * y[1];
    y[0] = y[1];
    y[1] = nextY;
   
    return extendedEuclid(divisor, dividend % divisor, y);
  }
}

int calculateN(int p, int q) {
  return p * q;
}

int calculateEulerTotient(int p, int q) {
  return (p -1) * (q - 1);
}


int calculateD(int inverseE, int eulersTotientOfN) {
  return (inverseE % eulersTotientOfN < 0 ? eulersTotientOfN + inverseE % eulersTotientOfN : inverseE % eulersTotientOfN);
}

void selectE(int eulersTotientOfN, int *e, int maxKeys) {
  int eVal, count;
  eVal = 0;
  count = 0;
  
  while(count < maxKeys) {
    eVal++;
    int y[2];
    y[0] = 0;
    y[1] = 0;
    if(eVal > 1 && eVal < eulersTotientOfN && extendedEuclid(eVal, eulersTotientOfN, y) == 1) {
      e[count++] = eVal;
    }
  }
}
