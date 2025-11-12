cmake_minimum_required(VERSION 3.13)
project(scientific_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")
set(SOURCES
    ${SRC_DIR}/calculator.cpp
)
# Detect Emscripten
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    message(STATUS "Building WebAssembly target with Emscripten...")

    # Define the target for WebAssembly
    add_executable(calculator ${SOURCES})

    # Emscripten link flags
    set_target_properties(calculator PROPERTIES
        OUTPUT_NAME "calculator"
        SUFFIX ".js"
        LINK_FLAGS "-s WASM=1 \             # Enable WebAssembly output
                    -s MODULARIZE=1 \.      # Modularize the output
                    -s EXPORT_NAME='createCalculatorModule' \.    # Export as a module
                    -s EXPORT_ES6=1 \.        # Use ES6 module format
                    -s ALLOW_MEMORY_GROWTH=1 \.    # Allow memory growth
                    -s EXPORTED_FUNCTIONS='[\"_add\",\"_subtract\",\"_multiply\",\"_divide\",\"_sin_deg\",\"_cos_deg\",\"_tan_deg\"]' \
                    -s EXPORTED_RUNTIME_METHODS='[\"cwrap\"]' \.      # Export cwrap method
                    -s ENVIRONMENT='web' \.      # Specify web environment
                    --no-entry"
    )
else()
    message(STATUS "Building native (non-WebAssembly) version...")
    add_library(calculator STATIC ${SOURCES})
    add_executable(calculator_exec ${SRC_DIR}/main.cpp)
    target_link_libraries(calculator_exec  calculator)
endif()
