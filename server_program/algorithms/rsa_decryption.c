#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform modular exponentiation (base^exp mod modulus)
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

// Function to perform RSA decryption
long long rsa_decrypt(long long ciphertext, long long d, long long n) {
    // Decrypt using modular exponentiation: ciphertext^d mod n
    return mod_exp(ciphertext, d, n);
}