# Linux Upstream Comparison

Trusted upstream reference:
- https://github.com/torvalds/linux

Relevant upstream files:
- `lib/reed_solomon/reed_solomon.c`
- `include/linux/rslib.h`
- `lib/reed_solomon/test_rslib.c`
- `Documentation/core-api/librs.rst`

## Current Repository Position

This repository preserves the **Linux 2.6.14** (Oct 2005) implementation of `rslib`. This era predates the major refactor in 2017 that separated the codec and control structures.

## Notable Differences vs Current Linux

1. **Object Model:** Current Linux uses a two-tier model (`struct rs_codec` and `struct rs_control`). This port uses a single-tier model where `rs_control` represents the full codec state.
2. **Memory Safety:** Current Linux pre-allocates decoding buffers in the control structure to avoid stack allocation. This port uses Variable Length Arrays (VLAs) in `decode_rs.h`.
3. **API:** Current Linux uses `init_rs_gfp`, while this port uses the legacy `init_rs`.

## Porting Strategy (Phase 5 Decision)

**Strategy Chosen: Option A (Preserve as historical userspace Linux port)**

**Rationale:**
- Breaking the public API to match modern Linux is not justified for the current use cases (e.g., Cryptagram).
- The historical port is stable, passes all characterization tests, and preserves the provenance of the 2005 era code.
- Specific bug fixes have been backported from modern Linux (e.g., formal derivative calculation fix in `decode_rs.h`).

## Backported Fixes

- **Formal Derivative Loop:** Corrected the loop range for calculating the formal derivative in the Berlekamp-Massey decoder.
- **Safety Checks:** Added NULL pointer checks in `free_rs` to align with modern kernel robustness.
- **Portability:** Replaced GNU-specific `typeof` with `__typeof__` and added `__extension__` markers to suppress warnings on modern compilers.
