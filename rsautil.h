#ifndef RSA_UTIL_H
#define RSA_UTIL_H

#include <stdint.h>

#define MAP_SIZE 67
extern const int RSA_MAP[];

void swap(int *a, int *b);
int modPower(int base, int exp, int n);
int charToDigit(char ch);
int digitToChar(uint16_t digit);

#endif