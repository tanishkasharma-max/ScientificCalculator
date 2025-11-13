import os


SRC_DIR = "src/cpp"
SOURCES = [os.path.join(SRC_DIR, "calculator.cpp")]
BUILD_DIR_NATIVE = "build/native"
BUILD_DIR_WASM = "build/wasm"

# === BUILD TYPE ===
BUILD_TYPE = ARGUMENTS.get("mode", "release")  # use `scons mode=debug` if needed


use_emscripten = ARGUMENTS.get("target", "") == "wasm"

if use_emscripten:
    print("🔧 Building WebAssembly target with Emscripten...")

    env = Environment(
        tools=[],
        ENV=os.environ,
        CXX="em++",
        CC="emcc",
        LINK="em++"
    )

    # WebAssembly flags 
    link_flags = [
        "-s", "WASM=1",
        "-s", "MODULARIZE=1",
        "-s", "EXPORT_NAME='createCalculatorModule'",
        "-s", "EXPORT_ES6=1",
        "-s", "ALLOW_MEMORY_GROWTH=1",
        "-s", "EXPORTED_FUNCTIONS=['_add','_subtract','_multiply','_divide','_sin_deg','_cos_deg','_tan_deg']",
        "-s", "EXPORTED_RUNTIME_METHODS=['cwrap']",
        "-s", "ENVIRONMENT='web'",
        "--no-entry"
    ]

    env.Append(LINKFLAGS=link_flags)

    # Output directory
    env['BUILD_DIR'] = BUILD_DIR_WASM
    env['TARGET_NAME'] = "calculator.js"

    # Build rule
    target = os.path.join(BUILD_DIR_WASM, "calculator.js")
    env.Command(target, SOURCES, f"mkdir -p {BUILD_DIR_WASM} && em++ -o {target} {' '.join(SOURCES)} {' '.join(link_flags)}")

    Default(target)

else:
    print("Building native...")

    env = Environment(ENV=os.environ)

    env.Append(CXXFLAGS=["-std=c++17", "-O2" if BUILD_TYPE == "release" else "-g"])

    # Create directories
    env['BUILD_DIR'] = BUILD_DIR_NATIVE
    env.Command(BUILD_DIR_NATIVE, None, f"mkdir -p {BUILD_DIR_NATIVE}")

    # Native static library
    lib = env.StaticLibrary(os.path.join(BUILD_DIR_NATIVE, "calculator"), SOURCES)

    # Executable
    main_src = os.path.join(SRC_DIR, "calculator.cpp")
    exe = env.Program(os.path.join(BUILD_DIR_NATIVE, "calculator_exec"), [main_src, lib])

    Default(exe)
