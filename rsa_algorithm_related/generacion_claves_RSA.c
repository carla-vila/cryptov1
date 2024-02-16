#include <stdio.h>

void generar_claves(int p, int q, int *e, int *d, int *n) {
    *n = p * q;
    int phi = (p - 1) * (q - 1);
    
    *e = 17; 
    *d = 0;
    while (((*d) * (*e)) % phi != 1) {
        (*d)++;
    }
}

int main() {

    int p = 61; 
    int q = 53; 
    int e, d, n;
    
    generar_claves(p, q, &e, &d, &n);
    
    printf("Clave pública (e, n): (%d, %d)\n", e, n);
    printf("Clave privada (d, n): (%d, %d)\n", d, n);

    return 0;
}