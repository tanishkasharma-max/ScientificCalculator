#!/bin/bash
# Scientific Calculator - Build Script
# Builds native and/or WebAssembly versions

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_ROOT"

echo "Scientific Calculator - Build"

BUILD_TYPE="${1:-Run}"
TARGET="${2:-native}" 


if [ "$TARGET" = "native" ] || [ "$TARGET" = "all" ]; then
  echo "Building Native Calculator..."
  echo ""
    cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

  
  echo ""
  echo "Native build complete!"
  echo "  Executable: ./build/calculator_exec"
  echo ""
  
  if [ -f "./build/calculator_exec" ]; then
    echo "Running native executable:"
    echo "---"
    ./build/calculator_exec
    echo "---"
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
    
    echo ""
    echo "WASM build complete!"
    echo ""
  fi
fi
