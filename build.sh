#!/bin/bash
# Scientific Calculator - Build Script
# Builds native and/or WebAssembly versions

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_ROOT"

echo "Scientific Calculator - Build"

# Parse arguments
BUILD_TYPE="${1:-Run}"
TARGET="${2:-native}" 


if [ "$TARGET" = "native" ] || [ "$TARGET" = "all" ]; then
  echo "Building Native Calculator..."
  echo ""
  
  # Clean and configure
  rm -rf build
  cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
  
  # Compile
  cmake --build build --config "$BUILD_TYPE"
  
  echo ""
  echo "Native build complete!"
  echo "  Executable: ./build/calculator_exec"
  echo ""
  
  # Run it
  if [ -f "./build/calculator_exec" ]; then
    echo "Running native executable:"
    echo "---"
    ./build/calculator_exec
    echo "---"
    echo ""
  fi
fi

fi

