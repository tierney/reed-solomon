/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rslib.h"

enum {
  kMessageBytes = 223,
  kParityBytes = 32
};

static void fill_payload(uint8_t *data) {
  int i;
  for (i = 0; i < kMessageBytes; ++i)
    data[i] = (uint8_t) i;
}

static int run_correctable_test(void) {
  int i;
  int corrected;
  int error_positions[16] = {
      0, 3, 10, 22, 31, 48, 64, 79, 95, 111, 127, 143, 159, 175, 191, 222
  };
  struct rs_control *rs = init_rs(8, 0x187, 0, 1, kParityBytes);
  uint16_t parity[kParityBytes];
  uint8_t original[kMessageBytes];
  uint8_t working[kMessageBytes];

  if (rs == NULL) {
    fprintf(stderr, "init_rs failed\n");
    return 1;
  }

  fill_payload(original);
  memcpy(working, original, sizeof(working));
  memset(parity, 0, sizeof(parity));

  if (encode_rs8(rs, working, kMessageBytes, parity, 0) != 0) {
    fprintf(stderr, "encode_rs8 failed\n");
    free_rs(rs);
    return 1;
  }

  for (i = 0; i < 16; ++i)
    working[error_positions[i]] ^= (uint8_t) (0x5A + i);

  corrected = decode_rs8(rs, working, parity, kMessageBytes, NULL, 0, NULL, 0, NULL);
  if (corrected < 0) {
    fprintf(stderr, "decode_rs8 failed on a correctable payload: %d\n", corrected);
    free_rs(rs);
    return 1;
  }

  if (memcmp(working, original, sizeof(working)) != 0) {
    fprintf(stderr, "decoded payload mismatch after correction\n");
    free_rs(rs);
    return 1;
  }

  free_rs(rs);
  return 0;
}

static int run_uncorrectable_test(void) {
  int i;
  int corrected;
  int error_positions[17] = {
      1, 4, 8, 12, 20, 27, 35, 44, 56, 67, 78, 90, 102, 145, 167, 199, 221
  };
  struct rs_control *rs = init_rs(8, 0x187, 0, 1, kParityBytes);
  uint16_t parity[kParityBytes];
  uint8_t payload[kMessageBytes];

  if (rs == NULL) {
    fprintf(stderr, "init_rs failed\n");
    return 1;
  }

  fill_payload(payload);
  memset(parity, 0, sizeof(parity));

  if (encode_rs8(rs, payload, kMessageBytes, parity, 0) != 0) {
    fprintf(stderr, "encode_rs8 failed\n");
    free_rs(rs);
    return 1;
  }

  for (i = 0; i < 17; ++i)
    payload[error_positions[i]] ^= (uint8_t) (0x33 + i);

  corrected = decode_rs8(rs, payload, parity, kMessageBytes, NULL, 0, NULL, 0, NULL);
  if (corrected >= 0) {
    fprintf(stderr, "expected uncorrectable decode result, got %d\n", corrected);
    free_rs(rs);
    return 1;
  }

  free_rs(rs);
  return 0;
}

int main(void) {
  if (run_correctable_test() != 0)
    return 1;

  if (run_uncorrectable_test() != 0)
    return 1;

  return 0;
}
