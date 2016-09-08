#include "rsalib.h"

void generateKeys(int p, int q, RsaKey **pr, RsaKey **pu, int maxKeys) {
  int n;
  n = calculateN(p, q);
  
  int eulersTotient;
  eulersTotient = calculateEulerTotient(p, q);
  
  int *e;
  e = (int *)malloc(sizeof(int) * maxKeys);
  selectE(eulersTotient, e, maxKeys);

  int i;
  for(i = 0; i < maxKeys; i++) {
    int y[2];
    y[0] = 0;
    y[1] = 1;
    
    pu[i]->n = n;
    pu[i]->value = e[i];
    pr[i]->n = n;
    
    int gcd;
    gcd = extendedEuclid(eulersTotient, e[i], y);
    pr[i]->value = calculateD(y[0], eulersTotient);
  }
}

void getDigitFromChar(int *holder, char ch) {
  if((*holder = charToDigit(ch)) == -1) {
    fprintf(stderr, "Failed to mapped character to digit\n");
  }
}

void getCharFromDigit(int *holder, uint16_t digits) {
  if((*holder = digitToChar(digits)) == -1) {
    fprintf(stderr, "Failed to map digit to character\n");
  }
}

void encrypt(RsaKey *pu, char *message, int size, uint32_t **ciphertext) {
  int i, k;
  for(i = 0, k = 0; i < size; i += 2) {
    int holder;
    getDigitFromChar(&holder, message[i]);
    
    uint32_t ch;
    ch = 0;
    ch = (uint32_t)(holder * DIGIT_SHIFT);
    
    getDigitFromChar(&holder, message[i + 1]);
    ch += (uint32_t)holder;
    (*ciphertext)[k] = modPower(ch, pu->value, pu->n);
    
    k++;
  }
}

void decrypt(RsaKey *pr, char **message, int size, uint32_t **ciphertext) {
  int i, k;
  for(i = 0, k = 0; i < size; i += 2) {
    uint16_t upperDigits, lowerDigits;
    upperDigits = 0;
    lowerDigits = 0;
        
    uint32_t ch;
    ch = 0;
    ch = modPower((*ciphertext)[k], pr->value, pr->n);
    
    int holder;
    upperDigits = ch / DIGIT_SHIFT;
    getCharFromDigit(&holder, upperDigits);
    (*message)[i] = holder;
    
    lowerDigits = ch - (upperDigits * 100);
    getCharFromDigit(&holder, lowerDigits);
    (*message)[i + 1] = holder;
    
    k++;
  }
}
