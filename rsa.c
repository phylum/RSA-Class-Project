#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rsalib.h"

#define MAX_KEYS 5
#define BORDER "---------------------------------------"
#define ERR_MSG "Failed to allocate memory\n"
#define MEM_ERR fprintf(stderr, ERR_MSG); exit(1)
#define FREE_PTR(ptr) free(ptr);ptr = NULL

void allocCiphertext(uint32_t **ciphertext, size_t size);
void allocKeys(RsaKey ***pr, RsaKey ***pu);
void allocPlaintext(char **plaintext, size_t size);
void display(char *message, int msgSize, int size, RsaKey **pr, RsaKey **pu, uint32_t **ciphertext, char **plaintext);
void displayCiphertext(uint32_t *ciphertext, int size);
void memoryCleanup(RsaKey ***pr, RsaKey ***pu, uint32_t **ciphertext, char **plaintext);

int main(void) {
  RsaKey **pr;
  RsaKey **pu;
  pr = pu = NULL;
  int p, q;
  p = 73;
  q = 151;
  
  printf("Creating keys...\n");
  allocKeys(&pr, &pu);
  generateKeys(p, q, pr, pu, MAX_KEYS);
  
  char *message0 = { "How are you?" };
  char *plaintext;
  plaintext = NULL;
  int msgSize;
  msgSize = strlen(message0);
  
  allocPlaintext(&plaintext, msgSize);
  
  uint32_t *ciphertext;
  ciphertext = NULL;
  int cipherSize;
  cipherSize = msgSize / 2;
  
  allocCiphertext(&ciphertext, cipherSize * sizeof(uint32_t));
  
  printf("\nDisplaying first message encrypted and decrypted with all five keys:");
  display(message0, msgSize, cipherSize, pr, pu, &ciphertext, &plaintext);
  
  FREE_PTR(ciphertext);
  FREE_PTR(plaintext);
  
  char *message1 = { "Public key cryptography." };
  msgSize = strlen(message1);
  cipherSize = msgSize / 2;
  
  allocPlaintext(&plaintext, msgSize);
  allocCiphertext(&ciphertext, cipherSize * sizeof(uint32_t));
  
  printf("\nDisplaying second message encrypted and decrypted with all five keys:");
  display(message1, msgSize, cipherSize, pr, pu, &ciphertext, &plaintext);
  
  memoryCleanup(&pr, &pu, &ciphertext, &plaintext);
  
  return 0;
}

void allocCiphertext(uint32_t **ciphertext, size_t size) {
  if( (*ciphertext = (uint32_t *)malloc(size)) == 0) {
    MEM_ERR;
  }
}

void allocKeys(RsaKey ***pr, RsaKey ***pu) {
  if((*pr = (RsaKey **)malloc(MAX_KEYS * sizeof(RsaKey))) == NULL) {
      MEM_ERR;
  }
  if((*pu = (RsaKey **)malloc(MAX_KEYS * sizeof(RsaKey))) == NULL) {
      MEM_ERR;
  }
  
  int j;
  for(j = 0; j < MAX_KEYS; j++) {
   if(((*pr)[j] = (RsaKey *)malloc(sizeof(RsaKey))) == NULL) {
      MEM_ERR;
   }
   if(((*pu)[j] = (RsaKey *)malloc(sizeof(RsaKey))) == NULL) {
      MEM_ERR;
   } 
  }
}

void allocPlaintext(char **plaintext, size_t size) {
  if( (*plaintext = (char *)malloc(size + 1)) == 0) {
    MEM_ERR;
  }
  (*plaintext)[size] = 0;
}

void display(char *message, int msgSize, int size, RsaKey **pr, RsaKey **pu, uint32_t **ciphertext, char **plaintext) {
  printf("\n%s%s\n", BORDER, BORDER);
  
  int j;
  for(j = 0; j < MAX_KEYS; j++) {
    printf("Key: %3d\tPR = { %6d, %6d }\t\tPU = { %6d, %6d }\n\n", j, pr[j]->value, pr[j]->n, pu[j]->value, pu[j]->n);
    printf("Message:    %s\n", message);
    
    encrypt(pu[j], message, msgSize, &*ciphertext);
    displayCiphertext(*ciphertext, size);
    
    decrypt(pr[j], &*plaintext, 2 * size, &*ciphertext);
    printf("Plaintext:  %s\n", *plaintext);
    printf("%s%s\n", BORDER, BORDER);
  }
}

void displayCiphertext(uint32_t *ciphertext, int size) {
  printf("Ciphertext: ");
  int i;
  for(i = 0; i < size; i++) {
    printf("%u ", ciphertext[i]);
  }
  printf("\n");
}

void memoryCleanup(RsaKey ***pr, RsaKey ***pu, uint32_t **ciphertext, char **plaintext) {
  FREE_PTR(*ciphertext);
  FREE_PTR(*plaintext);
  
  int i;
  for(i = 0; i < MAX_KEYS; i++) {
    FREE_PTR((*pr)[i]);
    FREE_PTR((*pu)[i]);
  }
  
  FREE_PTR(*pr);
  FREE_PTR(*pu);
}
