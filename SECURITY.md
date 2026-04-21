# SECURITY

This repository contains forward error correction code, not cryptography.

## Reporting

Please report suspected memory safety bugs, correctness regressions, and build
or packaging vulnerabilities by opening a private security advisory or issue in
the repository.

## Scope Notes

- Reed-Solomon correction failure should never be treated as successful decode.
- Behavior changes in decoder return codes are security-relevant for callers.
- Provenance and licensing regressions are release-blocking governance issues.
