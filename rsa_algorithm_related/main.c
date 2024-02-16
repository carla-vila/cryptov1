#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "rsa.h"

// gcc -c rsa.c -o rsa.o
// gcc main.c rsa.o -o rsa_encrypt
// ./rsa_encrypt 1234 17 6113

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <plaintext> <public_key> <modulus>\n", argv[0]);
        return 1;
    }

    long long plaintext = atoll(argv[1]);
    long long public_key = atoll(argv[2]);
    long long modulus = atoll(argv[3]);

    while (1) {
        long long ciphertext = rsa_encrypt(plaintext, public_key, modulus);
        printf("Encrypted ciphertext: %lld\n", ciphertext);

        sleep(2);
    }

    return 0;
}