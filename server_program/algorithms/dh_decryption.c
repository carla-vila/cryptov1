#include "dh_decryption.h"
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
long long symmetric_decrypt(long long ciphertext, long long key) {
    return ciphertext ^ key;
}

long long dh_decrypt(long long ciphertext) {
    long long SHARED_SECRET = mod_exp(PUBLIC_KEY_CLIENT, PRIVATE_KEY_SERVER, P);
    long long decrypted_data = symmetric_decrypt(ciphertext, SHARED_SECRET); 
    printf("Decrypted data: %lld\n", decrypted_data);
    return decrypted_data;
}

int main() {
    long long ciphertext = 123456785;

    // Decrypt the ciphertext using Diffie-Hellman decryption
    long long decrypted = dh_decrypt(ciphertext);

    return 0;
}