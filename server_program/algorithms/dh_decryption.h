#ifndef DH_ENCRYPTION_H
#define DH_ENCRYPTION_H

// Function declarations
long long mod_exp(long long base, long long exp, long long modulus);
long long dh_decrypt(long long ciphertext);

#endif /* DH_ENCRYPTION_H */