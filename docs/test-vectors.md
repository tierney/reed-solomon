# Test Vectors

This document describes the golden test vectors used to verify the RS(255,223) configuration.

## RS(255,223) Parameters
- **Symbol Size:** 8 bits
- **Primitive Polynomial:** 0x187 (x^8 + x^7 + x^2 + x + 1)
- **Roots:** 32
- **First Consecutive Root (fcr):** 0
- **Primitive Element (prim):** 1

## Golden Vectors

### Case 1: All Zeros
- **Input (223 bytes):** `00 00 ... 00`
- **Parity (32 symbols):** `0000 0000 ... 0000`

### Case 2: All Ones (0x01)
- **Input (223 bytes):** `01 01 ... 01`
- **Parity (32 symbols, hex):**
  `000d 007d 003c 00ed 0021 0062 00c4 0035`
  `00a5 005a 00a5 0085 00a7 0007 00d2 00c7`
  `00a1 00be 002e 00ea 0047 00ca 0051 00c6`
  `0096 0095 00dc 009b 00fb 002d 000b 0020`

### Case 3: Incrementing
- **Input (223 bytes):** `00 01 02 ... de`
- **Parity (32 symbols, hex):**
  `00b6 00dd 0035 008b 002e 0009 0076 0027`
  `00f6 00b0 00cc 00fd 0094 0095 0013 00f6`
  `002b 00da 0079 00fd 00cc 00be 00f6 00e7`
  `00ef 00e9 00b3 009d 006a 00e3 0026 007e`
