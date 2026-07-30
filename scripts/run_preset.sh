#!/usr/bin/env bash

set -e

PRESET="${1:-release}"

case "$PRESET" in
    release|component|system|all)
        ;;
    *)
        echo "Usage:"
        echo "  $0 [release|component|system|all]"
        exit 1
        ;;
esac

cmake --preset "$PRESET"
cmake --build --preset "$PRESET"

case "$PRESET" in
    component|system|all)
        ctest --preset "$PRESET"
        ;;
esac
