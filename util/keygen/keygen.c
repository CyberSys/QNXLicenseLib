#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pll.h"

void print_hex(const unsigned char* digest) {
    printf("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
                digest[0], digest[1], digest[2], digest[3],
                digest[4], digest[5], digest[6], digest[7],
                digest[8], digest[9], digest[10], digest[11],
                digest[12], digest[13], digest[14], digest[15]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: keygen <license key>\n");
        return EXIT_FAILURE;
    }
    char key[PLL_KEY_SIZE];
    int err = pll_get_open_key(key);
    if (err) {
        perror("pll_get_open_key");
        return EXIT_FAILURE;
    }

    err = pll_get_check_key(key, key, argv[1], strlen(argv[1]));
    if (err) {
        fprintf(stderr, "Invalid license key format\n");
        return EXIT_FAILURE;
    }

    print_hex((unsigned char*) key);
    printf("\n");

    return EXIT_SUCCESS;
}