#!/bin/bash

# format.sh — auto-format all C++ source files using clang-format

set -e  # stop on error

echo "Formatting C++ files..."

find src/ tests/ examples/ \
    -name "*.cpp" -o \
    -name "*.h"   -o \
    -name "*.hpp" \
    | xargs clang-format -i

echo "Done. All files formatted."