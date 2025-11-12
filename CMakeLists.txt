cmake_minimum_required(VERSION 3.13)
project(scientific_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(DEFINED ENV{EMSCRIPTEN})
    message(STATUS "Using Emscripten toolchain from $ENV{EMSCRIPTEN}")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake"
        CACHE FILEPATH "Emscripten toolchain file")
else()
    message(WARNING "EMSCRIPTEN not set. Please run: source /path/to/emsdk_env.sh before building for WebAssembly.")
endif()

# --- Source files ---
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")
add_library(calculator STATIC ${SRC_DIR}/calculator.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Building WebAssembly target...")

    set_target_properties(calculator PROPERTIES
        OUTPUT_NAME "calculator"
        LINK_FLAGS "-s WASM=1 \
                    -s MODULARIZE=1 \
                    -s EXPORT_NAME='createCalculatorModule' \
                    -s ALLOW_MEMORY_GROWTH=1 \
                    -s EXPORTED_FUNCTIONS='[\"_add\",\"_subtract\",\"_multiply\",\"_divide\",\"_sin_deg\",\"_cos_deg\",\"_tan_deg\",\"_power\",\"_square_root\",\"_natural_log\",\"_log_base\"]' \
                    -s EXPORTED_RUNTIME_METHODS='[\"cwrap\"]' \
                    --no-entry"
    )
else()
    message(STATUS "Building native (non-WebAssembly) version...")
    add_executable(calculator_exec ${SRC_DIR}/calculator.cpp)
     target_link_libraries(calculator_exec calculator)
endif()