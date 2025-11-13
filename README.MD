# Scientific Calculator

A multi-platform scientific calculator with native C++ support and WebAssembly integration. Build once, run everywhere: command-line (native), web browser (WASM), and TypeScript.



- **Core Operations**: Add, subtract, multiply, divide
- **Trigonometry**: Sine, cosine, tangent (in degrees)
- **Advanced Math**: Power, square root, natural logarithm
- **Multi-Platform**: 
  - Native C++ 
  - Web UI via WebAssembly
  - TypeScript library

## Project Structure

```
.
├── src/cpp/                    # C++ source code
│   ├── calculator.cpp          
│   └── calculator.hpp         
├── ts/                         
│   └── Calculator.ts           
├── web/                       
│   ├── src/
│   │   ├── main.ts             
│   │   ├── wasm_loader.js      
│   │   ├── style.css           
│   │  
│   ├── index.html              
│            
├── wasm/                          # given by emscripten
│   ├── calculator.js           
│   ├── calculator.wasm         
│   
├── build/                      
├── CMakeLists.txt              
├── package.json                
├── tsconfig.json               
└── build.sh                   
```


- **CMake** (≥ 3.13)
  ```bash
  cmake --version
  ```

### For WebAssembly Build
- **Emscripten SDK**
  ```bash
  git clone https://github.com/emscripten-core/emsdk.git
  cd emsdk
  ./emsdk install latest
  ./emsdk activate latest
  source ./emsdk_env.sh 
  ```


### 1. Build Native Calculator

```bash
# Using the build script 
./build.sh Run native

# Or manually
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/calculator_exec
```


### 2. Build WebAssembly Module

```bash
# Requires emsdk to be sourced
source /path/to/emsdk/emsdk_env.sh

# Build
./build.sh Run wasm

```

### 3. Run Web App (Development)

```bash
cd web
npm run dev
```

## Build Commands Reference

### Using `build.sh` Script

```bash
# Native
./build.sh  native

# WebAssembly only
./build.sh Run wasm


```


