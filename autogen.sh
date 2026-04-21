#!/bin/sh

set -eu

if ! command -v autoreconf >/dev/null 2>&1; then
  echo "error: autoreconf not found; install autoconf/automake/libtool" >&2
  exit 1
fi

if ! command -v automake >/dev/null 2>&1; then
  echo "error: automake not found; install automake" >&2
  exit 1
fi

autoreconf --install -v
automake -v --add-missing --copy
