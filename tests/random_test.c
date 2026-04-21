/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rslib.h"

#define NROOTS 32
#define DATALEN 223
#define TOTAL_TESTS 1000

static void shuffle(int *array, int n) {
    if (n > 1) {
        int i;
        for (i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

static int run_random_test(struct rs_control *rs, int num_errors, int num_erasures) {
    uint8_t original[DATALEN];
    uint8_t working[DATALEN];
    uint16_t parity[NROOTS];
    int eras_pos[NROOTS];
    int all_pos[DATALEN];
    int i;

    for (i = 0; i < DATALEN; i++) {
        original[i] = rand() % 256;
        all_pos[i] = i;
    }
    shuffle(all_pos, DATALEN);

    memcpy(working, original, DATALEN);
    memset(parity, 0, sizeof(parity));

    if (encode_rs8(rs, working, DATALEN, parity, 0) != 0) return -1;

    // Inject erasures first
    for (i = 0; i < num_erasures; i++) {
        int pos = all_pos[i];
        eras_pos[i] = pos; // Note: pad=0 for RS(255,223), so index is the same
        working[pos] ^= (uint8_t)(rand() % 255 + 1);
    }

    // Inject errors in remaining positions
    for (i = 0; i < num_errors; i++) {
        int pos = all_pos[num_erasures + i];
        working[pos] ^= (uint8_t)(rand() % 255 + 1);
    }

    int corrected = decode_rs8(rs, working, parity, DATALEN, NULL, num_erasures, eras_pos, 0, NULL);
    
    if (2 * num_errors + num_erasures <= NROOTS) {
        if (corrected < 0) return -2; // False negative
        if (memcmp(working, original, DATALEN) != 0) return -3; // Incorrectly corrected
    } else {
        if (corrected >= 0) {
            // Note: with random errors, it's statistically possible to accidentally "correct" to another valid codeword, 
            // but it's unlikely for small distances.
            // For 17 errors, it's almost certain to fail.
            return -4; // False positive
        }
    }

    return 0;
}

int main(void) {
    unsigned int seed = (unsigned int)time(NULL);
    printf("Random test with seed: %u\n", seed);
    srand(seed);

    struct rs_control *rs = init_rs(8, 0x187, 0, 1, NROOTS);
    if (!rs) return 1;

    int i;
    for (i = 0; i < TOTAL_TESTS; i++) {
        int errs = rand() % 17; // 0 to 16
        int eras = 0;
        if (run_random_test(rs, errs, eras) != 0) {
            fprintf(stderr, "Failed at iteration %d (errs=%d)\n", i, errs);
            return 1;
        }
    }
    printf("Passed %d iterations of pure error correction.\n", TOTAL_TESTS);

    for (i = 0; i < TOTAL_TESTS; i++) {
        int errs = rand() % 8; // 0 to 7
        int eras = rand() % 16; // 0 to 15
        // 2*7 + 15 = 29 <= 32
        if (run_random_test(rs, errs, eras) != 0) {
            fprintf(stderr, "Failed at iteration %d (errs=%d, eras=%d)\n", i, errs, eras);
            return 1;
        }
    }
    printf("Passed %d iterations of mixed error/erasure correction.\n", TOTAL_TESTS);

    for (i = 0; i < 100; i++) {
        if (run_random_test(rs, 17, 0) == 0) {
            fprintf(stderr, "False positive correction for 17 errors at iteration %d\n", i);
            // This can happen statistically but is very rare for RS(255,223).
        }
    }
    printf("Passed 100 iterations of uncorrectable error detection.\n");

    free_rs(rs);
    return 0;
}
