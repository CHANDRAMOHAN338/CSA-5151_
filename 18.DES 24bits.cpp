#include <stdio.h>
#include <stdint.h>

#define NUM_ROUNDS 16
#define KEY_SIZE 64
#define SUBKEY_SIZE 48
#define PC1_SIZE 56
#define PC2_SIZE 48

const int PC1[PC1_SIZE] = {
    57, 49, 41, 33, 25, 17, 9, 
    1, 58, 50, 42, 34, 26, 18, 
    10, 2, 59, 51, 43, 35, 27, 
    19, 11, 3, 60, 52, 44, 36, 
    63, 55, 47, 39, 31, 23, 15, 
    7, 62, 54, 46, 38, 30, 22, 
    14, 6, 61, 53, 45, 37, 29, 
    21, 13, 5, 28, 20, 12, 4
};

const int PC2[PC2_SIZE] = {
    14, 17, 11, 24, 1, 5, 
    3, 28, 15, 6, 21, 10, 
    23, 19, 12, 4, 26, 8, 
    16, 7, 27, 20, 13, 2, 
    41, 52, 31, 37, 47, 55, 
    30, 40, 51, 45, 33, 48, 
    44, 49, 39, 56, 34, 53, 
    46, 42, 50, 36, 29, 32
};

const int SHIFTS[NUM_ROUNDS] = {
    1, 1, 2, 2, 2, 2, 2, 2, 
    1, 2, 2, 2, 2, 2, 2, 1
};

void permute(const int *table, int n, const uint8_t *in, uint8_t *out) {
    for (int i = 0; i < n; i++)
        out[i] = in[table[i] - 1];
}

void rotate_left(uint8_t *key, int n, int bits) {
    uint8_t temp[28];
    for (int i = 0; i < bits; i++) {
        for (int j = 0; j < n - 1; j++)
            temp[j] = key[j + 1];
        temp[n - 1] = key[0];
        for (int j = 0; j < n; j++)
            key[j] = temp[j];
    }
}

void generate_subkeys(const uint8_t *key, uint8_t subkeys[NUM_ROUNDS][SUBKEY_SIZE]) {
    uint8_t permuted_key[PC1_SIZE];
    uint8_t left[28], right[28];

    permute(PC1, PC1_SIZE, key, permuted_key);

    for (int i = 0; i < 28; i++) {
        left[i] = permuted_key[i];
        right[i] = permuted_key[i + 28];
    }

    for (int round = 0; round < NUM_ROUNDS; round++) {
        rotate_left(left, 28, SHIFTS[round]);
        rotate_left(right, 28, SHIFTS[round]);

        uint8_t combined_key[56];
        for (int i = 0; i < 28; i++) {
            combined_key[i] = left[i];
            combined_key[i + 28] = right[i];
        }

        permute(PC2, PC2_SIZE, combined_key, subkeys[round]);
    }
}

int main() {
    uint8_t key[KEY_SIZE] = {
        0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1
    };

    uint8_t subkeys[NUM_ROUNDS][SUBKEY_SIZE];

    generate_subkeys(key, subkeys);
 printf("chandramohan - 192210338\n");
	printf("Subkeys:\n");
    for (int i = 0; i < NUM_ROUNDS; i++) {
        for (int j = 0; j < SUBKEY_SIZE; j++) {
            printf("%02X ", subkeys[i][j]);
        }
        printf("\n");
    }

    return 0;
}

