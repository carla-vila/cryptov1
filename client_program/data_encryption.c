#include <stdio.h>
#include <stdlib.h>
#include "data_encryption.h"
#include "./algorithms/rsa_encryption.h"
#include "./algorithms/dh_encryption.h"
#include "./algorithms/ec_encryption.h"


long long rsa_encrypt_data(double data, long long public_key, long long modulus) {
    char data_str[1024];
    snprintf(data_str, sizeof(data_str), "%.2f", data);
    return rsa_encrypt(atoll(data_str), public_key, modulus);
}

long long dh_encrypt_data(double data) {
    long long plaintext = (long long)data;
    return dh_encrypt(plaintext);
}

Point ec_encrypt_data(double data) {
    long long plaintext = (long long)data;
    return ec_encrypt(plaintext);
}