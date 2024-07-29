#include <stdio.h>
#include <math.h>

int main() {
    double log2_factorial = 0.0;

    for (int i = 1; i <= 25; i++) {
        log2_factorial += log2(i);
    }
 printf("chandramohan - 192210338\n");
	printf("Approximate number of keys for the Playfair cipher (as a power of 2): 2^%.2f\n", log2_factorial);

    return 0;
}
