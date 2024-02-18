#ifndef DH_H
#define DH_H

long long mod_exp(long long base, long long exp, long long modulus);
long long dh_decrypt(long long public_key_bob, long long private_key_alice, long long private_key_bob);

#endif 