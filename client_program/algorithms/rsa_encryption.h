#include "../data_encryption.h"
#ifndef RSA_H
#define RSA_H

#include <string.h> 

long long mod_exp(long long base, long long exp, long long modulus);
long long rsa_encrypt(long long plaintext);

#endif 