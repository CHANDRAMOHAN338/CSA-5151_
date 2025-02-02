#include <stdio.h>
#include <string.h>
void xorBlocks(const char *input1, const char *input2, char *output, int block_size) {
    for (int i = 0; i < block_size; ++i) {
        output[i] = input1[i] ^ input2[i];
    }
}
void cbcMacOneBlock(const char *key, const char *message, char *mac, int block_size) 
{
    xorBlocks(key, message, mac, block_size);
}
void cbcMacTwoBlocks(const char *key, const char *message, char *mac, int block_size) {
    char t[block_size];
    cbcMacOneBlock(key, message, t, block_size);
    xorBlocks(message + block_size, t, mac, block_size);
}
int main() {
    int block_size = 8; 
    char key[block_size] = "abcdefgh";
    char message[block_size] = "12345678";
    char mac[block_size];
    cbcMacOneBlock(key, message, mac, block_size);
    printf("One-block MAC: ");
    for (int i = 0; i < block_size; ++i) {
        printf("%02x", (unsigned char)mac[i]);
    }
    printf("\n");
    char messageTwoBlocks[2 * block_size] = "1234567812345678";
    char macTwoBlocks[block_size];
    cbcMacTwoBlocks(key, messageTwoBlocks, macTwoBlocks, block_size);
    printf("Two-block MAC: ");
    for (int i = 0; i < block_size; ++i) {
        printf("%02x", (unsigned char)macTwoBlocks[i]);
    }
    printf("\n");
    return 0;
}