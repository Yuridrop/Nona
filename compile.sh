#!/bin/bash

set -e

VCPKG_ROOT="/home/frieren/vcpkg"

# Create build dir
mkdir -p build
cd build

# Configure with toolchain
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DCMAKE_BUILD_TYPE=Debug

# Build the project
cmake --build .
