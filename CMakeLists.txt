cmake_minimum_required(VERSION 3.13)
project(scientific_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SRC_DIR "${PROJECT_SOURCE_DIR}/platforms/mac/src/cpp")
set(SOURCES
    ${SRC_DIR}/calculator.cpp
)


if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    message(STATUS "Building WebAssembly target with Emscripten...")

    # WASM sources
    set(WASM_SOURCES
        ${SOURCES}
        ${PROJECT_SOURCE_DIR}/platforms/web/wasm_export.cpp
    )

    add_executable(calculator ${WASM_SOURCES})

    target_include_directories(calculator PRIVATE
        ${SRC_DIR}
    )

    # FIX: Required for WASM linking + exceptions
    target_compile_options(calculator PRIVATE -fPIC -sDISABLE_EXCEPTION_CATCHING=0)

    # Emscripten Link Flags
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
                    -s DISABLE_EXCEPTION_CATCHING=0 \
                    --no-entry"
    )

else()
    message(STATUS "Building native version...")

    add_library(calculator STATIC ${SOURCES})

    add_executable(calculator_exec ${SRC_DIR}/calculator.cpp)
    target_link_libraries(calculator_exec calculator)
endif()



