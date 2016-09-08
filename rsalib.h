#ifndef RSA_LIB_H
#define RSA_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rsakey.h"
#include "rsautil.h"

#define DIGIT_SHIFT 100

void getDigitFromChar(int *holder, char ch);
void getCharFromDigit(int *holder, uint16_t digits);
void generateKeys(int p, int q, RsaKey **pr, RsaKey **pu, int maxKeys);
void encrypt(RsaKey *pu, char *message, int size, uint32_t **ciphertext);
void decrypt(RsaKey *pr, char **message, int size, uint32_t **ciphertext);

#endif