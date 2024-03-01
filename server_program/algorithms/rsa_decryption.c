#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PRIVATE_KEY_B 2753
#define SERVER_PRIVATE_KEY_N 3233

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

long long rsa_decrypt(long long ciphertext) {
    return mod_exp(ciphertext, SERVER_PRIVATE_KEY_B, SERVER_PRIVATE_KEY_N);
}

int main() {
    long long ciphertext = 855; 
    long long decrypted_text = rsa_decrypt(ciphertext);
    printf("Decrypted plaintext: %lld\n", decrypted_text);
    return 0;
}