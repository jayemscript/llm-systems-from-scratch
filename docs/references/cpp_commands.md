# C++ + CMake Workflow Reference

Use this every time you add a new phase (tensor, matmul, attention, etc.)

---

## What CMake Actually Does

```
Your code → CMake → Makefiles/Ninja → g++ compiles → executable
```

CMake is a **build system generator** — it doesn't compile directly.
It reads your `CMakeLists.txt` files and generates the real build instructions.

| Tool | Role |
|------|------|
| `CMake` | Generates build files, manages dependencies, finds libraries |
| `make` / `ninja` | Reads generated files and runs the actual compiler |
| `g++` | The compiler that turns `.cpp` into an executable |

---

## One-Time Setup (per machine)

```bash
# Check you have everything
g++ --version
cmake --version       # need 3.20+
```

---

## Project Setup (per phase)

When you add a new phase (e.g. `matmul`), do these steps:

### 1. Create your source file

```
src/matmul/main.cpp
src/matmul/matmul.h
src/matmul/matmul.cpp
```

### 2. Create `src/matmul/CMakeLists.txt`

```cmake
add_executable(matmul_main main.cpp matmul.cpp)

target_include_directories(matmul_main PRIVATE
    ${CMAKE_SOURCE_DIR}/src/matmul
)

target_compile_options(matmul_main PRIVATE -Wall -Wextra)
```

### 3. Register it in root `CMakeLists.txt`

```cmake
add_subdirectory(src/tensor)
add_subdirectory(src/matmul)   # ← add this line
```

### 4. Create `tests/matmul/CMakeLists.txt`

```cmake
add_executable(test_matmul test_matmul.cpp
    ${CMAKE_SOURCE_DIR}/src/matmul/matmul.cpp
)

target_include_directories(test_matmul PRIVATE
    ${CMAKE_SOURCE_DIR}/src/matmul
)

add_test(NAME MatmulTest COMMAND test_matmul)
```

### 5. Register test in root `CMakeLists.txt`

```cmake
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests/tensor)
    add_subdirectory(tests/matmul)   # ← add this line
endif()
```

---

## Build

```bash
# First time — configure + generate
mkdir -p build && cd build
cmake ..

# Every time after — just build
cmake --build .

# Build only one specific target
cmake --build . --target matmul_main

# Clean build (wipe everything and start fresh)
cd ..
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
```

> Always run cmake commands from inside the `build/` folder.
> Always run scripts from the **project root**.

---

## Run

```bash
# From project root, after building
./build/src/tensor/tensor_main
./build/src/matmul/matmul_main
```

Or use the build script:

```bash
chmod +x scripts/build.sh   # one time only
./scripts/build.sh
```

---

## Test

```bash
cd build

# Run all tests
ctest

# Run with output (see pass/fail details)
ctest --output-on-failure

# Run only tests matching a name
ctest -R Matmul

# Run verbosely
ctest -V
```

---

## Debug

### Step 1 — Build with debug symbols

```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Step 2 — Run with gdb

```bash
gdb ./src/matmul/matmul_main
```

### Common gdb commands

```bash
run                  # start the program
break main           # set breakpoint at main
break matmul.cpp:42  # set breakpoint at line 42
next                 # step over (next line)
step                 # step into (enter function)
print x              # print value of variable x
backtrace            # show call stack
quit                 # exit gdb
```

### Build types

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug          # debug symbols, no optimization
cmake .. -DCMAKE_BUILD_TYPE=Release        # optimized, no debug symbols
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo # optimized + debug symbols
```

> Re-run `cmake ..` when switching build types.

---

## Check for Warnings

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . 2>&1 | grep warning
```

| Flag | What it catches |
|------|----------------|
| `-Wall` | Common mistakes (unused vars, missing returns) |
| `-Wextra` | Extra checks (signed/unsigned mismatch, etc.) |
| `-Werror` | (optional) Treat warnings as errors |

To add `-Werror` per module:
```cmake
target_compile_options(matmul_main PRIVATE -Wall -Wextra -Werror)
```

---

## Format Code

```bash
# Format a single file
clang-format -i src/matmul/matmul.cpp

# Format all .cpp and .h files
find src/ -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Or use your script
./scripts/format.sh
```

---

## Checklist — Adding a New Phase

Copy this every time:

```
[ ] Create src/<phase>/  with main.cpp and any .h/.cpp files
[ ] Create src/<phase>/CMakeLists.txt
[ ] Add add_subdirectory(src/<phase>) to root CMakeLists.txt
[ ] Create tests/<phase>/test_<phase>.cpp
[ ] Create tests/<phase>/CMakeLists.txt
[ ] Add add_subdirectory(tests/<phase>) under BUILD_TESTS in root CMakeLists.txt
[ ] cd build && cmake .. && cmake --build .
[ ] ctest -R <Phase> to verify tests pass
```

---

## Quick Reference Summary

| Goal | Command |
|------|---------|
| Configure project | `cd build && cmake ..` |
| Build everything | `cmake --build .` |
| Build one target | `cmake --build . --target matmul_main` |
| Run executable | `./build/src/matmul/matmul_main` |
| Run all tests | `cd build && ctest` |
| Run tests verbose | `cd build && ctest --output-on-failure` |
| Debug build | `cmake .. -DCMAKE_BUILD_TYPE=Debug` |
| Release build | `cmake .. -DCMAKE_BUILD_TYPE=Release` |
| Start debugger | `gdb ./build/src/matmul/matmul_main` |
| Format all code | `find src/ -name "*.cpp" -o -name "*.h" \| xargs clang-format -i` |
| Clean build | `rm -rf build && mkdir build` |