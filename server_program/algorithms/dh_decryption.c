#include "dh_encryption.h"
#include <stdio.h>

#define P 23    
#define G 5     
#define PRIVATE_KEY_SERVER 3 // Server's private key
#define PUBLIC_KEY_CLIENT 7  // Client's public key

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

long long dh_decrypt(long long ciphertext) {
    long long SHARED_SECRET = mod_exp(PUBLIC_KEY_CLIENT, PRIVATE_KEY_SERVER, P);
    long long decrypted_data = mod_exp(ciphertext, SHARED_SECRET, P); 
    printf("Decrypted data: %lld\n", decrypted_data);
    return decrypted_data;
}
