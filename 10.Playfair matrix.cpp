#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void preparePlayfairMatrix(char matrix[SIZE][SIZE]) {
    char predefinedMatrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    memcpy(matrix, predefinedMatrix, sizeof(predefinedMatrix));
}

void prepareText(char *input, char *output) {
    int i, j = 0;
    int len = strlen(input);

    for (i = 0; i < len; ++i) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i] == 'J' ? 'I' : input[i]);
        }
    }
    output[j] = '\0';

    len = strlen(output);

    for (i = 0; i < len; i += 2) {
        if (output[i] == output[i + 1]) {
            memmove(output + i + 2, output + i + 1, len - i);
            output[i + 1] = 'X';
            len++;
        }
    }

    if (len % 2 != 0) {
        output[len] = 'X';
        output[len + 1] = '\0';
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPlayfair(char plaintext[], char matrix[SIZE][SIZE], char ciphertext[]) {
    int len = strlen(plaintext);
    int i, r1, c1, r2, c2;

    for (i = 0; i < len; i += 2) {
        findPosition(matrix, plaintext[i], &r1, &c1);
        findPosition(matrix, plaintext[i + 1], &r2, &c2);

        if (r1 == r2) {
            ciphertext[i] = matrix[r1][(c1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[r2][(c2 + 1) % SIZE];
        } else if (c1 == c2) {
            ciphertext[i] = matrix[(r1 + 1) % SIZE][c1];
            ciphertext[i + 1] = matrix[(r2 + 1) % SIZE][c2];
        } else {
            ciphertext[i] = matrix[r1][c2];
            ciphertext[i + 1] = matrix[r2][c1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char matrix[SIZE][SIZE];
    char plaintext[] = "Must see you over Cadogan West. Coming at once";
    char preparedText[100];
    char ciphertext[100];

    preparePlayfairMatrix(matrix);
    prepareText(plaintext, preparedText);

    printf("Prepared plaintext: %s\n", preparedText);

    encryptPlayfair(preparedText, matrix, ciphertext);

    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}
