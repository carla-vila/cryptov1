#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A_PARAM 2
#define B_PARAM 2
#define P_PARAM 17
#define G_X_PARAM 5
#define G_Y_PARAM 1
#define N_PARAM 19

typedef struct {
    int x;
    int y;
} Point;

// Function to calculate modular inverse
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;
        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to add two points on the elliptic curve
Point add(Point P, Point Q, int a, int p) {
    Point R;
    int lambda;

    // Check if P = Q
    if (P.x == Q.x && P.y == Q.y) {
        lambda = ((3 * P.x * P.x) + a) * modInverse(2 * P.y, p) % p;
    } else {
        lambda = (Q.y - P.y) * modInverse(Q.x - P.x, p) % p;
    }

    R.x = (lambda * lambda - P.x - Q.x) % p;
    R.y = (lambda * (P.x - R.x) - P.y) % p;

    // Make sure x and y are positive
    if (R.x < 0) R.x += p;
    if (R.y < 0) R.y += p;

    return R;
}

// Function to calculate scalar multiplication of a point on the elliptic curve
Point scalarMultiply(Point P, int k, int a, int p) {
    Point Q = P;
    for (int i = 1; i < k; i++) {
        Q = add(Q, P, a, p);
    }
    return Q;
}

int main() {
    Point G = {G_X_PARAM, G_Y_PARAM}; // Base point
    Point Q = scalarMultiply(G, N_PARAM, A_PARAM, P_PARAM); // Public key

    printf("Elliptic curve parameters:\n");
    printf("A: %d\n", A_PARAM);
    printf("B: %d\n", B_PARAM);
    printf("P (prime modulus): %d\n", P_PARAM);
    printf("Base point G = (%d, %d)\n", G.x, G.y);
    printf("Order of G (N): %d\n", N_PARAM);
    printf("Public key Q = (%d, %d)\n", Q.x, Q.y);

    return 0;
}
