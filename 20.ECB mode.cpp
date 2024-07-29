#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *out, int len) {
    for (int i = 0; i < len; i++)
        out[i] = a[i] ^ b[i];
}

void des_encrypt_block(uint8_t *in, uint8_t *out, uint8_t *key);
void des_decrypt_block(uint8_t *in, uint8_t *out, uint8_t *key);

void ecb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, int len, uint8_t *key) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        des_encrypt_block(plaintext + i, ciphertext + i, key);
    }
}

void ecb_decrypt(uint8_t *ciphertext, uint8_t *plaintext, int len, uint8_t *key) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        des_decrypt_block(ciphertext + i, plaintext + i, key);
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, int len, uint8_t *iv, uint8_t *key) {
    uint8_t block[BLOCK_SIZE], temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, temp, block, BLOCK_SIZE);
        des_encrypt_block(block, ciphertext + i, key);
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}

void cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext, int len, uint8_t *iv, uint8_t *key) {
    uint8_t block[BLOCK_SIZE], temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        des_decrypt_block(ciphertext + i, block, key);
        xor_blocks(block, temp, plaintext + i, BLOCK_SIZE);
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t plaintext[16] = "Hello, ECB!";
    uint8_t ciphertext[16];
    uint8_t decrypted[16];

    ecb_encrypt(plaintext, ciphertext, 16, key);
    ecb_decrypt(ciphertext, decrypted, 16, key);
     printf("chandramohan - 192210338\n");
	printf("ECB Mode\n");
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) printf("%02X ", ciphertext[i]);
    printf("\nDecrypted: %s\n", decrypted);

    cbc_encrypt(plaintext, ciphertext, 16, iv, key);
    cbc_decrypt(ciphertext, decrypted, 16, iv, key);

    printf("\nCBC Mode\n");
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) printf("%02X ", ciphertext[i]);
    printf("\nDecrypted: %s\n", decrypted);

    return 0;
}

void des_encrypt_block(uint8_t *in, uint8_t *out, uint8_t *key) {
    // Placeholder for DES encryption
    memcpy(out, in, BLOCK_SIZE);  // Copy input to output as dummy implementation
}

void des_decrypt_block(uint8_t *in, uint8_t *out, uint8_t *key) {
    // Placeholder for DES decryption
    memcpy(out, in, BLOCK_SIZE);  // Copy input to output as dummy implementation
}

