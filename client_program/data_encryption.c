#include <stdio.h>
#include <stdlib.h>
#include "./algorithms/rsa_encryption.h"

long long encrypt_data(double data, long long public_key, long long modulus) {
    char data_str[1024];
    snprintf(data_str, sizeof(data_str), "%.2f", data);
    return rsa_encrypt(atoll(data_str), public_key, modulus);
}