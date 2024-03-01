#ifndef EC_DECRYPTION_H
#define EC_DECRYPTION_H

// Define the Point struct
typedef struct {
    int x;
    int y;
} Point;

// Function prototype for elliptic curve decryption
long long ec_decrypt(long long r);

#endif /* EC_DECRYPTION_H */