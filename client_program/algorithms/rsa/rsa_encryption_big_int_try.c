#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 100
#define BASE 10

typedef struct {
    int digits[MAX_DIGITS];
    int num_digits;
} BigInt;

void init_bigint(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->num_digits = 0;
}

void add_bigint(const BigInt *a, const BigInt *b, BigInt *result) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int sum = carry + a->digits[i] + b->digits[i];
        result->digits[i] = sum % BASE;
        carry = sum / BASE;
    }
    result->num_digits = MAX_DIGITS; // This is incorrect
}

void multiply_bigint(const BigInt *a, const BigInt *b, BigInt *result) {
    BigInt temp;
    init_bigint(&temp);
    for (int i = 0; i < MAX_DIGITS; i++) {
        for (int j = 0; j < MAX_DIGITS - i; j++) {
            temp.digits[i + j] += a->digits[i] * b->digits[j];
        }
    }
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int sum = carry + temp.digits[i];
        result->digits[i] = sum % BASE;
        carry = sum / BASE;
    }
    result->num_digits = MAX_DIGITS; // This is incorrect
}

void mod_exp(const BigInt *base, const BigInt *exp, const BigInt *modulus, BigInt *result) {
    BigInt res;
    init_bigint(&res);
    res.digits[0] = 1;
    res.num_digits = 1;

    BigInt base_copy;
    init_bigint(&base_copy);
    memcpy(&base_copy, base, sizeof(BigInt));

    BigInt exp_copy;
    init_bigint(&exp_copy);
    memcpy(&exp_copy, exp, sizeof(BigInt));

    while (exp_copy.num_digits > 0 || exp_copy.digits[0] > 0) {
        if ((exp_copy.digits[0] % 2) == 1) {
            multiply_bigint(&res, &base_copy, &res);
            multiply_bigint(&res, &base_copy, &res); // Performing square once is sufficient
            multiply_bigint(&res, modulus, &res); // Perform modulus operation after each multiplication
        }
        multiply_bigint(&base_copy, &base_copy, &base_copy);
        multiply_bigint(&base_copy, modulus, &base_copy); // Perform modulus operation after each multiplication
        exp_copy.digits[0] /= 2;
    }
    memcpy(result, &res, sizeof(BigInt));
}

BigInt SERVER_PUBLIC_KEY_E, SERVER_PUBLIC_KEY_N;
BigInt SERVER_PRIVATE_KEY_D;

void init_rsa_keys() {
    init_bigint(&SERVER_PUBLIC_KEY_E);
    init_bigint(&SERVER_PUBLIC_KEY_N);
    init_bigint(&SERVER_PRIVATE_KEY_D);

    SERVER_PUBLIC_KEY_E.digits[0] = 65537; 
    SERVER_PUBLIC_KEY_E.num_digits = 1;
    
    SERVER_PUBLIC_KEY_N.digits[0] = 3233;
    SERVER_PUBLIC_KEY_N.num_digits = 1;
    
    SERVER_PRIVATE_KEY_D.digits[0] = 2753; 
    SERVER_PRIVATE_KEY_D.num_digits = 1;
}

void rsa_encrypt(const BigInt *plaintext, BigInt *ciphertext) {
    mod_exp(plaintext, &SERVER_PUBLIC_KEY_E, &SERVER_PUBLIC_KEY_N, ciphertext);
}

void rsa_decrypt(const BigInt *ciphertext, BigInt *plaintext) {
    mod_exp(ciphertext, &SERVER_PRIVATE_KEY_D, &SERVER_PUBLIC_KEY_N, plaintext);
}

int main() {
    BigInt plaintext, ciphertext, decrypted_text;
    init_rsa_keys();
    init_bigint(&plaintext);
    init_bigint(&ciphertext);
    init_bigint(&decrypted_text);

    plaintext.digits[0] = 123; 
    plaintext.num_digits = 1;

    rsa_encrypt(&plaintext, &ciphertext);

    printf("Ciphertext: ");
    for (int i = ciphertext.num_digits - 1; i >= 0; i--) {
        printf("%d", ciphertext.digits[i]);
    }
    printf("\n");
    
    rsa_decrypt(&ciphertext, &decrypted_text);
    
    printf("Decrypted text: ");
    for (int i = decrypted_text.num_digits - 1; i >= 0; i--) {
        printf("%d", decrypted_text.digits[i]);
    }
    printf("\n");    
    return 0;
}
