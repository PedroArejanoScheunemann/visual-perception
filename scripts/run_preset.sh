#!/usr/bin/env bash

set -e

PRESET="${1:-release}"

case "$PRESET" in
    release|component|system|test-all|benchmark)
        ;;
    *)
        echo "Usage:"
        echo "  $0 [release|component|system|test-all|benchmark]"
        exit 1
        ;;
esac

cmake --preset "$PRESET"
cmake --build --preset "$PRESET"

case "$PRESET" in
    component|system|test-all|benchmark)
        ctest --preset "$PRESET"
        ;;
esac
