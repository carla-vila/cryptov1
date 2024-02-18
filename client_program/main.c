#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "data_encryption.h"
#include "socket_communication.h"
#include "./algorithms/rsa_encryption.h"


///Running the code
//gcc main.c data_encryption.c socket_communication.c ./algorithms/rsa_encryption.c -o main_program
//./main_program <algorithm> <public_key> <moduluss>

double collect_humidity_data() {
    //return rand() % 101;
    return 25;
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <algorithm> <public_key> <modulus>\n", argv[0]);
        return 1;
    }
    long long algorithm_used = atoll(argv[1]);
    long long public_key = atoll(argv[2]);
    long long modulus = atoll(argv[3]);

    double humidity = collect_humidity_data();
    long long encrypted_data = 0;
    if (strcmp(argv[1], "rsa") == 0) {
        encrypted_data = encrypt_data(humidity, public_key, modulus);
    } else {
        printf("Unsupported encryption algorithm: %s\n", argv[1]);
        return 1;
    }
    
    send_encrypted_data(encrypted_data);
    return 0;
}