# MSYS2 Setup — Windows

Run all commands in **MSYS2 MSYS** terminal.

---

## One-Time Full Install

Copy and run all at once:

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
pacman -S mingw-w64-ucrt-x86_64-clang
pacman -S mingw-w64-ucrt-x86_64-fmt
pacman -S mingw-w64-ucrt-x86_64-ninja
pacman -S mingw-w64-ucrt-x86_64-gdb
```

---

## What Each Package Does

| Package | What it installs |
|---------|-----------------|
| `mingw-w64-ucrt-x86_64-cmake` | CMake build system |
| `base-devel mingw-w64-ucrt-x86_64-toolchain` | g++, gcc, make, and core build tools |
| `mingw-w64-ucrt-x86_64-clang` | clang-format for code formatting |
| `mingw-w64-ucrt-x86_64-fmt` | `{fmt}` library for string formatting |
| `mingw-w64-ucrt-x86_64-ninja` | Ninja build system (faster than make) |
| `mingw-w64-ucrt-x86_64-gdb` | Debugger |

---

## Verify Everything Works

```bash
cmake --version
g++ --version
clang-format --version
gdb --version
ninja --version
```

---

## Packages to Add Per Phase

As the project grows, install these when needed:

```bash
# Phase 5+ — linear algebra (fast matrix ops)
pacman -S mingw-w64-ucrt-x86_64-openblas

# Phase 14 — Python bindings
pacman -S mingw-w64-ucrt-x86_64-python
pacman -S mingw-w64-ucrt-x86_64-pybind11

# Phase 15 — Rust
# Download rustup from https://rustup.rs instead of pacman
```

---

## Update All Packages

Run occasionally to keep everything up to date:

```bash
pacman -Syu
```