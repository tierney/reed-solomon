# Cryptagram Use Case

## Historical Context

Cryptagram was a system designed to allow users to share encrypted images on social media platforms (like Facebook or Instagram) that perform lossy image compression (JPEG).

Since encryption randomizes the data, even a single bit flip in the encrypted payload can make the entire block un-decryptable. JPEG compression, while preserving visual features, does not preserve exact byte values.

## Role of Reed-Solomon

To survive the "lossy channel" of social media recompression, Cryptagram used **Forward Error Correction (FEC)**.

1. **Encoding:** The encrypted payload was encoded using RS(255,223). This added 32 bytes of parity for every 223 bytes of data.
2. **Robustness:** This specific configuration allows for correcting up to **16 byte-errors** in every 255-byte block.
3. **JPEG Adaptation:** By choosing appropriate RS parameters and interleaving, the payload could be made robust enough to survive the quantization and rounding errors inherent in high-quality JPEG compression.

## Implementation Details

- **RS(255,223)**: A standard "NASA" configuration often used in telecommunications.
- **Generator Polynomial 0x187**: Specifically chosen for its properties in $GF(2^8)$.
- **Systematic Coding**: The data symbols appear unchanged in the codeword, with parity symbols appended at the end.

This library preserves the exact implementation used during the Cryptagram era, ensuring that historical payloads can still be decoded and recovered.
