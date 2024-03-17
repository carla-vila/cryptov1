#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {
    int ret = 1;
    RSA *rsa_keypair = NULL;
    BIGNUM *bne = NULL;
    BIO *bp_public = NULL, *bp_private = NULL;
    char message[1024] = "Este es el mensaje a encriptar.";
    unsigned char encrypted[4098] = {};
    unsigned char decrypted[4098] = {};

    int bits = 1024; // Tamaño de la clave en bits
    unsigned long e = RSA_F4; // Exponente público común

    // Inicializar la biblioteca de errores
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    // Generar la clave RSA
    bne = BN_new();
    if (!BN_set_word(bne, e))
        handleErrors();

    rsa_keypair = RSA_new();
    if (!RSA_generate_key_ex(rsa_keypair, bits, bne, NULL))
        handleErrors();

    // Guardar las claves en archivos
    bp_public = BIO_new_file("public.pem", "w+");
    ret = PEM_write_bio_RSAPublicKey(bp_public, rsa_keypair);
    if (ret != 1)
        handleErrors();

    bp_private = BIO_new_file("private.pem", "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, rsa_keypair, NULL, NULL, 0, NULL, NULL);
    if (ret != 1)
        handleErrors();

    // Encriptar el mensaje
    ret = RSA_public_encrypt(strlen(message) + 1, (unsigned char*)message, encrypted, rsa_keypair, RSA_PKCS1_OAEP_PADDING);
    if(ret < 0)
        handleErrors();

    printf("Mensaje encriptado: %s\n", encrypted);

    // Desencriptar el mensaje
    ret = RSA_private_decrypt(ret, encrypted, decrypted, rsa_keypair, RSA_PKCS1_OAEP_PADDING);
    if(ret < 0)
        handleErrors();

    printf("Mensaje desencriptado: %s\n", decrypted);

    // Liberar memoria
    RSA_free(rsa_keypair);
    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    BN_free(bne);

    // Limpieza
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

    return 0;
}
