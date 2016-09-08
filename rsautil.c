#include "rsautil.h"

const int RSA_MAP[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
                        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                        'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', ' ', '.', ',', ';', '?' };

void swap(int *a, int *b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int modPower(int base, int exp, int n) {
  return (exp == 1 ? base : (base * modPower(base, exp - 1, n)) % n);
}

int charToDigit(char ch) {
  int i;
  for(i = 0; i < MAP_SIZE; i++) {
    if(ch == RSA_MAP[i])
      return i;
  }
  return -1;
}

int digitToChar(uint16_t digit) {
  return (digit < MAP_SIZE ? RSA_MAP[digit] : -1);
}
