#include "dh_decryption.h"
#include <stdio.h>

#define P 23    // Prime number
#define G 5     // Primitive root of P

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

// Function for Diffie-Hellman key exchange
long long dh_decrypt(long long public_key_bob, long long private_key_alice, long long private_key_bob) {
    long long public_key_alice = mod_exp(G, private_key_alice, P);  
    long long shared_secret = mod_exp(public_key_bob, private_key_alice, P);
    return shared_secret;
}