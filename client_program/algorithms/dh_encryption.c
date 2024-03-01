#include <stdio.h>
#include "../data_encryption.h"
#include "dh_encryption.h"

#define P 23    
#define G 5     
#define PRIVATE_KEY_CLIENT 6
#define PUBLIC_KEY_SERVER 7


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

long long symmetric_encrypt(long long plaintext, long long key) {
    return plaintext ^ key;
}

long long dh_encrypt(long long plaintext) {
    long long PUBLIC_KEY_CLIENT = mod_exp(G, PRIVATE_KEY_CLIENT, P);  
    long long SHARED_SECRET = mod_exp(PUBLIC_KEY_SERVER, PRIVATE_KEY_CLIENT, P);
    long long encrypted_data = symmetric_encrypt(plaintext, SHARED_SECRET); 
    printf("Encrypted data: %lld\n", encrypted_data);
    return encrypted_data;
}


int main() {
    long long plaintext = 123456789;
    long long encrypted = dh_encrypt(plaintext);
    printf("Encrypted text: %lld\n", encrypted);
    return 0;
}