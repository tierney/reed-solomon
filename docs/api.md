# API Documentation

The library provides a generic Reed-Solomon encoder/decoder with a runtime-configurable object model.

## Core API (C)

### Codec Initialization

```c
struct rs_control *init_rs(int symsize, int gfpoly, int fcr, int prim, int nroots);
```
- **symsize**: Symbol size in bits (e.g., 8 for 8-bit symbols).
- **gfpoly**: Primitive polynomial for the Galois Field (e.g., 0x187).
- **fcr**: First consecutive root of the generator polynomial (index form).
- **prim**: Primitive element to generate roots.
- **nroots**: Number of parity symbols (correction capacity is `nroots / 2`).

Returns a pointer to an `rs_control` structure or `NULL` on failure. Codecs are cached and ref-counted based on their parameters.

### Encoding

```c
int encode_rs8(struct rs_control *rs, uint8_t *data, int len, uint16_t *par, uint16_t invmsk);
```
- **rs**: The codec control structure.
- **data**: The data buffer (symbols).
- **len**: Length of the data buffer.
- **par**: Parity buffer (size must be at least `nroots`). **Must be initialized to 0 by the caller.**
- **invmsk**: Mask to XOR with data (usually 0).

### Decoding

```c
int decode_rs8(struct rs_control *rs, uint8_t *data, uint16_t *par, int len,
               uint16_t *s, int no_eras, int *eras_pos, uint16_t invmsk,
               uint16_t *corr);
```
- **data**: The received data buffer (corrected in-place).
- **par**: The received parity buffer.
- **no_eras**: Number of erasures.
- **eras_pos**: Positions of erasures (relative to the full codeword).
- **corr**: Optional buffer to store correction bitmask.

Returns the number of corrected symbols or `-EBADMSG` if uncorrectable.

### Resource Cleanup

```c
void free_rs(struct rs_control *rs);
```
Decrements the reference count of the codec and frees resources if it reaches zero.

## C++ Wrapper

The project includes a simple C++ wrapper in `rs_codec.h` / `rs_codec.cc` for easier integration.

```cpp
#include "rs_codec.h"

// Example usage
ReedSolomonCodec codec(8, 0x187, 0, 1, 32);
codec.Encode(data, len, parity);
int errors = codec.Decode(data, parity, len);
```

## Parameter Compatibility (Cryptagram)

For Cryptagram-compatible RS(255,223):
- `symsize = 8`
- `gfpoly = 0x187`
- `fcr = 0`
- `prim = 1`
- `nroots = 32`
