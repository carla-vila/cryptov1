#include <stdio.h>
#include <stdlib.h>

#define P 23    // Prime number
#define G 5     // Primitive root of P

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

int main() {
    long long private_key_bob = 6;  
    long long public_key_bob = mod_exp(G, private_key_bob, P);  

    printf("Bob's public key: %lld\n", public_key_bob);

    // Receive Alice's public key
    long long public_key_alice;
    printf("Enter Alice's public key: ");
    scanf("%lld", &public_key_alice);

    // Calculate shared secret
    long long shared_secret = mod_exp(public_key_alice, private_key_bob, P);

    printf("Shared secret: %lld\n", shared_secret);

    return 0;
}