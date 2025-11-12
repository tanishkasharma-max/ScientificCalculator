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

if [ "$TARGET" = "android" ] || [ "$TARGET" = "all" ]; then
  echo "Building Android Calculator..."
  echo ""

  if [ -z "$ANDROID_NDK_HOME" ]; then
    echo "⚠ ANDROID_NDK_HOME not set. Please set it to your Android NDK path."
    exit 1
  fi

  rm -rf build/android
  cmake -S . -B build/android \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
        -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
        -DANDROID_ABI="arm64-v8a" \
        -DANDROID_PLATFORM=android-21

  cmake --build build/android --config "$BUILD_TYPE"

  echo ""
  echo "Android build complete!"
  echo "  Output: build/android/libcalculator.so (or executable)"
  echo ""
fi



if [ "$TARGET" = "wasm" ] || [ "$TARGET" = "all" ]; then
  echo "Building WebAssembly Module..."
  echo ""
  

  if ! command -v emcmake &> /dev/null; then
    echo "⚠ Emscripten not found. Skipping WASM build."
    echo "  To build WASM: source /path/to/emsdk/emsdk_env.sh"
    echo ""
  else
    # Clean and configure for Emscripten
    rm -rf wasm/build
    emcmake cmake -S . -B wasm/build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    
    # Compile
    cmake --build wasm/build --config "$BUILD_TYPE"
    
    echo ""
    echo "WASM build complete!"
    echo "  Files generated in: wasm/build/"
    echo "  - calculator.js"
    echo "  - calculator.wasm"
    echo ""
  fi
fi
