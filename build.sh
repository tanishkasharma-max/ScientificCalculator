#!/bin/bash
# Scientific Calculator - Build Script
# Builds native and/or WebAssembly versions

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_ROOT"

echo "Scientific Calculator - Build"

BUILD_TYPE="${1:-Run}"
TARGET="${2:-native}" 

if [ "$TARGET" = "test" ]; then
  echo "Running C++ Tests..."

  mkdir -p build/tests

  g++ -std=c++17 test/test.cpp src/cpp/calculator.cpp -o build/tests/test_bin

  echo ""
  echo "Running test executable:"
  echo "---"
  ./build/tests/test_bin
  echo "---"

  exit 0
fi


if [ "$TARGET" = "native"]; then
  echo "Building Native Calculator..."
  echo ""
    cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

  
  echo ""
  echo "Native build complete!"
  echo "  Executable: ./build/calculator_exec"
  echo ""
  
  if [ -f "./build/calculator_exec" ]; then
    echo "Running native executable:"

    ./build/calculator_exec
    echo ""
  fi
fi


if [ "$TARGET" = "wasm" ] || [ "$TARGET" = "all" ]; then
  echo "Building WebAssembly Module..."
  echo ""
  

  if ! command -v emcmake &> /dev/null; then
    echo " Emscripten not found. Skipping WASM build."
    echo " To build WASM: source /path/to/emsdk/emsdk_env.sh"
    echo ""
  else
    
    emcmake cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    
    # Compile
    cmake --build build --config "$BUILD_TYPE"
    
    echo "WASM build complete!"
  fi
fi
