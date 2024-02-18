#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mod_exp(long long base, long long exp, long long modulus) {
    long long result = 1;
    base %= modulus;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        exp >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

long long rsa_decrypt(long long ciphertext, long long d, long long n) {
    return mod_exp(ciphertext, d, n);
}