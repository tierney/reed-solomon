# LICENSE AUDIT

This document is a technical provenance and licensing audit. It is not legal
advice.

## Summary

The core Reed-Solomon implementation in this repository is derived from Linux
kernel Reed-Solomon sources and contains GPLv2-era attribution and notices in
the code comments.

Historically, this repository included a top-level `COPYING` file containing
the GPL-3.0 license text while core source files described GPLv2 terms. That
was a mismatch and release risk.

This repository is now aligned to treat Linux-derived code as
`GPL-2.0-only`.

## Scope Reviewed

- `COPYING`
- `README`
- `src/reed_solomon.c`
- `src/rslib.h`
- `src/encode_rs.h`
- `src/decode_rs.h`
- `src/list.h`
- `src/poison.h`
- `src/rs_codec.h`
- `src/rs_codec.cc`
- `src/rs_main.cc`

## Findings

1. Linux-derived files preserve explicit attribution to Thomas Gleixner and
   Phil Karn and retain GPLv2-era comments.
2. The code structure and identifiers map directly to Linux kernel
   Reed-Solomon sources from an older upstream era.
3. SPDX tags have been added in-tree to clarify file-level licensing intent.
4. This repository now treats the codebase as GPL-2.0-only for release and
   distribution purposes unless future provenance work identifies exceptions.

## File-Level Licensing Intent

- `src/reed_solomon.c`: GPL-2.0-only, Linux-derived
- `src/rslib.h`: GPL-2.0-only, Linux-derived
- `src/encode_rs.h`: GPL-2.0-only, Linux-derived
- `src/decode_rs.h`: GPL-2.0-only, Linux-derived
- `src/list.h`: GPL-2.0-only, Linux-derived adaptation
- `src/poison.h`: GPL-2.0-only, Linux-derived adaptation
- `src/rs_codec.h`: GPL-2.0-only project wrapper
- `src/rs_codec.cc`: GPL-2.0-only project wrapper
- `src/rs_main.cc`: GPL-2.0-only example program

## Outstanding Items

1. Capture exact upstream commit hashes for all imported Linux-derived files.
2. Expand provenance references in `docs/linux-provenance.md` as hashes are
   confirmed.
3. Keep attribution comments intact during future refactors and syncs.
