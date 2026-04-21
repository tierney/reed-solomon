# Project Status

- **Build:** Hardened Autotools build passing on macOS and Linux.
- **Tests:** Full characterization suite passing, including golden vectors for RS(255,223) and property-based randomized tests.
- **Licensing:** Audited and aligned to GPL-2.0-only. SPDX headers in place.
- **Provenance:** Identified as a port from Linux 2.6.14 (Oct 2005).
- **Maintenance:** Preserved as a historical userspace port with targeted bug fixes backported from modern Linux.

## Known Limitations

- **API:** Uses legacy 2005-era `rslib` API.
- **Memory:** Uses stack-allocated VLAs for decoding buffers.
- **Concurrency:** Basic thread-safety provided by a global mutex around the codec list.
