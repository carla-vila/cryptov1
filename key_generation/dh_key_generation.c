#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define P 23
#define G 5

// Function to calculate modulo exponentiation
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
    srand(time(NULL)); // Seed for random number generation

    // Generate private keys for both client and server
    long long private_key_client = rand() % (P - 1) + 1;
    long long private_key_server = rand() % (P - 1) + 1;

    // Calculate public keys for both client and server
    long long public_key_client = mod_exp(G, private_key_client, P);
    long long public_key_server = mod_exp(G, private_key_server, P);

    // Print the generated keys
    printf("Client's private key: %lld\n", private_key_client);
    printf("Client's public key: %lld\n", public_key_client);
    printf("Server's private key: %lld\n", private_key_server);
    printf("Server's public key: %lld\n", public_key_server);

    return 0;
}