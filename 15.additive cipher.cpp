#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

const double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

void calculateFrequencies(const char *text, double frequencies[ALPHABET_SIZE]) {
    int len = strlen(text);
    int counts[ALPHABET_SIZE] = {0};

    for (int i = 0; i < len; ++i) {
        if (isalpha(text[i])) {
            counts[tolower(text[i]) - 'a']++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        frequencies[i] = (double)counts[i] / len * 100;
    }
}

double chiSquared(const double observed[ALPHABET_SIZE]) {
    double chiSq = 0.0;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        double expected = englishFrequencies[i];
        chiSq += ((observed[i] - expected) * (observed[i] - expected)) / expected;
    }

    return chiSq;
}

void decrypt(char *ciphertext, int key, char *plaintext) {
    int len = strlen(ciphertext);

    for (int i = 0; i < len; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = (ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

void findBestDecryptions(char *ciphertext, int topN) {
    char plaintext[1000];
    double frequencies[ALPHABET_SIZE];
    double chiSquares[ALPHABET_SIZE];
    int keys[ALPHABET_SIZE];

    for (int key = 0; key < ALPHABET_SIZE; ++key) {
        decrypt(ciphertext, key, plaintext);
        calculateFrequencies(plaintext, frequencies);
        chiSquares[key] = chiSquared(frequencies);
        keys[key] = key;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; ++i) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; ++j) {
            if (chiSquares[j] > chiSquares[j + 1]) {
                double tempChi = chiSquares[j];
                chiSquares[j] = chiSquares[j + 1];
                chiSquares[j + 1] = tempChi;

                int tempKey = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = tempKey;
            }
        }
    }

    for (int i = 0; i < topN; ++i) {
        decrypt(ciphertext, keys[i], plaintext);
        printf("Key: %d, Chi-Squared: %.2f, Plaintext: %s\n", keys[i], chiSquares[i], plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int topN;
 printf("chandramohan - 192210338\n");
	printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    findBestDecryptions(ciphertext, topN);

    return 0;
}

