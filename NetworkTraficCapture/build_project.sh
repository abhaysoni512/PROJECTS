#!/bin/bash
# Build script for NetworkTraficCapture
set -e

# Step 1: Go to project root
cd "$(dirname "$0")"

# Step 2: Create build directory if it doesn't exist
mkdir -p build
cd build

# Step 3: Run CMake
cmake ..

# Step 4: Build with make
make

echo "\nBuild complete!"
echo "If you want to use the Python bindings, ensure packet_capture.so is in your PYTHONPATH or copy it to your python/ directory."
