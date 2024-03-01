#include <string.h> 
#include "../data_encryption.h"
#include "rsa_encryption.h"

#define SERVER_PUBLIC_KEY_E 17
#define SERVER_PUBLIC_KEY_N 3233

long long mod_expp(long long base, long long exp, long long modulus) {
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

long long rsa_encrypt(long long plaintext) {
    return mod_expp(plaintext, SERVER_PUBLIC_KEY_E, SERVER_PUBLIC_KEY_E);
}