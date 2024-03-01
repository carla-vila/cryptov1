#ifndef EC_DECRYPTION_H
#define EC_DECRYPTION_H

// Define the Point struct
typedef struct {
    int x;
    int y;
} Point;

// Function prototype for elliptic curve decryption
long long ec_decrypt(Point R);

#endif /* EC_DECRYPTION_H */