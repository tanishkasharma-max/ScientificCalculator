cmake_minimum_required(VERSION 3.13)
project(scientific_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")
set(SOURCES
    ${SRC_DIR}/calculator.cpp
)
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(TEST_SOURCES
    ${TEST_DIR}/test.cpp
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
        LINK_FLAGS "-s WASM=1 \
                    -s MODULARIZE=1 \
                    -s EXPORT_NAME='createCalculatorModule' \
                    -s EXPORT_ES6=1 \
                    -s ALLOW_MEMORY_GROWTH=1 \
                    -s EXPORTED_RUNTIME_METHODS='[\"cwrap\"]' \
                    -s ENVIRONMENT='web' \
                    --no-entry"
    )
else()
    message(STATUS "Building native version...")
    add_library(calculator STATIC ${SOURCES})
    add_executable(calculator_exec ${SRC_DIR}/calculator.cpp)
    target_link_libraries(calculator_exec calculator)
endif()

