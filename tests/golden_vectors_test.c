/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rslib.h"

static int test_golden_vector(const char *name, uint8_t *data, int data_len, uint16_t *expected_parity, int parity_len) {
    struct rs_control *rs = init_rs(8, 0x187, 0, 1, parity_len);
    if (!rs) {
        fprintf(stderr, "%s: init_rs failed\n", name);
        return 1;
    }

    uint16_t par[32];
    memset(par, 0, sizeof(par));
    encode_rs8(rs, data, data_len, par, 0);

    for (int i = 0; i < parity_len; i++) {
        if (par[i] != expected_parity[i]) {
            fprintf(stderr, "%s: parity mismatch at index %d: expected %04x, got %04x\n", name, i, expected_parity[i], par[i]);
            free_rs(rs);
            return 1;
        }
    }

    // Also verify decoding
    int numerr = decode_rs8(rs, data, par, data_len, NULL, 0, NULL, 0, NULL);
    if (numerr < 0) {
        fprintf(stderr, "%s: decoding of golden vector failed: %d\n", name, numerr);
        free_rs(rs);
        return 1;
    }

    free_rs(rs);
    printf("%s: PASS\n", name);
    return 0;
}

int main(void) {
    uint8_t data[223];
    uint16_t expected_parity[32];

    // Case 1: All zeros
    memset(data, 0, sizeof(data));
    memset(expected_parity, 0, sizeof(expected_parity));
    if (test_golden_vector("All Zeros", data, 223, expected_parity, 32) != 0) return 1;

    // Case 2: All ones (0x01)
    memset(data, 1, sizeof(data));
    uint16_t p2[32] = {
        0x000d, 0x007d, 0x003c, 0x00ed, 0x0021, 0x0062, 0x00c4, 0x0035,
        0x00a5, 0x005a, 0x00a5, 0x0085, 0x00a7, 0x0007, 0x00d2, 0x00c7,
        0x00a1, 0x00be, 0x002e, 0x00ea, 0x0047, 0x00ca, 0x0051, 0x00c6,
        0x0096, 0x0095, 0x00dc, 0x009b, 0x00fb, 0x002d, 0x000b, 0x0020
    };
    if (test_golden_vector("All Ones", data, 223, p2, 32) != 0) return 1;

    // Case 3: Incrementing
    for (int i = 0; i < 223; i++) data[i] = i;
    uint16_t p3[32] = {
        0x00b6, 0x00dd, 0x0035, 0x008b, 0x002e, 0x0009, 0x0076, 0x0027,
        0x00f6, 0x00b0, 0x00cc, 0x00fd, 0x0094, 0x0095, 0x0013, 0x00f6,
        0x002b, 0x00da, 0x0079, 0x00fd, 0x00cc, 0x00be, 0x00f6, 0x00e7,
        0x00ef, 0x00e9, 0x00b3, 0x009d, 0x006a, 0x00e3, 0x0026, 0x007e
    };
    if (test_golden_vector("Incrementing", data, 223, p3, 32) != 0) return 1;

    return 0;
}
