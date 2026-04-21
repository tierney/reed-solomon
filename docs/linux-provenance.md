# Linux Provenance

This repository is a userspace port of Linux kernel Reed-Solomon library code.

## Source Mapping

- `src/reed_solomon.c` <- `lib/reed_solomon/reed_solomon.c`
- `src/rslib.h` <- `include/linux/rslib.h`
- `src/encode_rs.h` <- `lib/reed_solomon/encode_rs.c` (ported as include body)
- `src/decode_rs.h` <- `lib/reed_solomon/decode_rs.c` (ported as include body)

Additional Linux-derived support headers:
- `src/list.h` <- `include/linux/list.h` adaptation
- `src/poison.h` <- Linux poison/debug header adaptation

## Evidence

The core files preserve CVS `$Id` lines and attribution comments referencing
Thomas Gleixner and Phil Karn with 2005-era revision markers.

The repository import history indicates local import in 2012, while the code
text itself maps to older Linux upstream source form.

## Userspace Adaptations

- Linux headers replaced with local headers and libc/pthread headers.
- Kernel allocators replaced with `malloc`/`free`.
- Kernel mutex replaced with `pthread_mutex_t`.
- Module infrastructure removed.

## Preservation Rules

1. Keep original Linux attribution comments.
2. Keep SPDX tags and license statements aligned with Linux-derived origin.
3. Document every non-trivial upstream sync in
   `docs/linux-upstream-comparison.md`.
