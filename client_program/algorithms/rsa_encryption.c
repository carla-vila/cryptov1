#include "rsa_encryption.h"
#include <string.h> // Include the string.h header for strlen function

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

// Function to perform RSA encryption
long long rsa_encrypt(long long plaintext, long long e, long long n) {
    return mod_exp(plaintext, e, n);
}