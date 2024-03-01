#ifndef DATA_ENCRYPTION_H
#define DATA_ENCRYPTION_H

typedef struct {
    int x;
    int y;
} Point;

long long rsa_encrypt_data(double data, long long public_key, long long modulus);
long long dh_encrypt_data(double data);
Point ec_encrypt_data(double data);

#endif 
