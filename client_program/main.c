#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "data_encryption.h"
#include "socket_communication.h"
#include "./algorithms/rsa_encryption.h"
#include "./algorithms/ec_encryption.h"
#include "./algorithms/dh_encryption.h"




///Running the code
//gcc main.c data_encryption.c socket_communication.c ./algorithms/rsa_encryption.c ./algorithms/dh_encryption.c ./algorithms/ec_encryption.c -o main_program
//./main_program <algorithm> <public_key> <moduluss>

double collect_data() {
    //return rand() % 101;
    return 25;
}

long long point_to_long_long(Point point) {
    long long encoded_point = ((long long)point.x << 32) | (unsigned int)point.y;
    return encoded_point;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <algorithm> <public_key> <modulus>\n", argv[0]);
        return 1;
    }
    long long algorithm_used = atoll(argv[1]);
    long long public_key = atoll(argv[2]);
    long long modulus = atoll(argv[3]);

    double data = collect_data();
    long long encrypted_data = 0;
    Point R = {0, 0};

    if (strcmp(argv[1], "rsa") == 0) {
        encrypted_data = rsa_encrypt_data(data, public_key, modulus);
    } else if (strcmp(argv[1], "dh") == 0) {
        encrypted_data = dh_encrypt_data(data);

    } else if (strcmp(argv[1], "ec") == 0){
        R = ec_encrypt_data(data);
        encrypted_data = point_to_long_long(R);

    }else {
        printf("Unsupported encryption algorithm: %s\n", argv[1]);
        return 1;
    }
    
    send_encrypted_data(encrypted_data);

    return 0;
}