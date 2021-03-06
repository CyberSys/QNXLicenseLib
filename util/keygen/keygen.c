//! Утилита для получения проверочного ключа
/*!
 * @file
 * @author  Александр Половцев (sasha_polo@mail.ru)
 * @date    31.05.2013
 *
 * Утилите в качестве входных параметров передается флаг и строка с лицензионным ключом.
 * На данный момент формат лицензионного ключа - 16 символов без разделитилей
 * Например:
 * @code
 *     keygen.out -open
 *     keygen.out -check AAAAAAAAAAAAAAAA
 * @endcode
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pll.h"

//! Функция, для вывода хэша md5 в шестнадцатеричном формате.
/*!
 * @param digest строка, содержащая хэш md5.
 */
void print_hex(const unsigned char* digest) {
    printf("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
                digest[0], digest[1], digest[2], digest[3],
                digest[4], digest[5], digest[6], digest[7],
                digest[8], digest[9], digest[10], digest[11],
                digest[12], digest[13], digest[14], digest[15]);
}

//! Функция, содержащая код утилиты
/*!
 * Алгоритм работы:
 * 1. Парсинг входных параметров.
 * 2. В зависимости от флага - получение открытого или проверочного ключа.
 * 3. Вывод результата на экран.
 *
 * @retval EXIT_SUCCESS в случае успеха
 * @retval EXIT_FAILURE в остальных случаях
 */
int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: keygen <flag> [license key]\n");
        return EXIT_FAILURE;
    }

    char key[PLL_KEY_SIZE];
    int err = pll_get_open_key(key);
    if (err == -1) {
        perror("pll_get_open_key");
        return EXIT_FAILURE;
    }
    if (!strncmp(argv[1], "-open", 6)) {
        print_hex((unsigned char*) key);
        fputc('\n', stdout);
    } else if (!strncmp(argv[1], "-check", 7)) {
        if (argc != 3) {
            fprintf(stderr, "Usage: keygen <flag> [license key]\n");
            return EXIT_FAILURE;
        }
        err = pll_get_check_key(key, key, argv[2], strlen(argv[2]));
        if (err) {
            fprintf(stderr, "Invalid license key format\n");
            return EXIT_FAILURE;
        }
        print_hex((unsigned char*) key);
        fputc('\n', stdout);
    } else {
        fprintf(stderr, "Error: unknown flag %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
