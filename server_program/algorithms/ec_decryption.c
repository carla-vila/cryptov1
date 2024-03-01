#include <stdio.h>
#include "dh_decryption.h"
// Definition of the elliptic curve parameters
#define A_PARAM 2
#define B_PARAM 2
#define P_PARAM 17

#define PRIVATE_KEY 7

typedef struct {
    int x;
    int y;
} Point;


long long point_to_long_long(Point point) {
    long long encoded_point = ((long long)point.x << 32) | (unsigned int)point.y;
    return encoded_point;
}
Point long_long_to_point(long long encoded_point) {
    Point point;
    point.x = encoded_point >> 32;
    point.y = encoded_point & 0xFFFFFFFF;
    return point;
}


int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

Point add(Point P, Point Q, int a, int p) {
    Point R;
    int lambda;
    if (P.x == Q.x && P.y == Q.y) {
        lambda = ((3 * P.x * P.x) + a) * modInverse(2 * P.y, p) % p;
    } else {
        lambda = (Q.y - P.y) * modInverse(Q.x - P.x, p) % p;
    }
    R.x = (lambda * lambda - P.x - Q.x) % p;
    R.y = (lambda * (P.x - R.x) - P.y) % p;
    if (R.x < 0) R.x += p;
    if (R.y < 0) R.y += p;
    return R;
}

Point scalarMultiply(Point P, int k, int a, int p) {
    Point Q = P;
    for (int i = 1; i < k; i++) {
        Q = add(Q, P, a, p);
    }
    return Q;
}

long long ec_decrypt(long long r) {
    Point R = long_long_to_point(r);
    int inv_private_key = modInverse(17, P_PARAM);
    // Perform scalar multiplication with the inverse of the private key modulus
    Point plaintext_point = scalarMultiply(R, inv_private_key, A_PARAM, P_PARAM);
    long long plaintext = plaintext_point.x;
    return plaintext;
}

/* int main() {
    long long encrypted_point = 60129542159; // Example encrypted point
    long long decrypted_data = ec_decrypt(encrypted_point);
    printf("Decrypted plaintext: %lld\n", decrypted_data);
    return 0;
} */