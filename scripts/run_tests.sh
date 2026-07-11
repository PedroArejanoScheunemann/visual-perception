#!/usr/bin/env bash

set -e

TARGET="${1:-all}"

case "$TARGET" in
    unit|integration|system|all)
        ;;
    *)
        echo "Usage:"
        echo "  $0 [unit|integration|system|all]"
        exit 1
        ;;
esac

cmake --preset "$TARGET"
cmake --build --preset "$TARGET"
ctest --preset "$TARGET"
