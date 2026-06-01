# Windows Development Setup — MSYS2

> This project is currently developed on Windows using MSYS2.
> Linux setup will be added in a future update.

---

## What is MSYS2

MSYS2 is a software distribution and building platform for Windows.
It provides a Unix-like terminal (bash), a package manager (pacman), and
pre-built packages for tools like g++, cmake, clang, gdb, and more.

Reference: https://www.msys2.org/

---

## Step 1 — Install MSYS2

1. Download the installer from https://www.msys2.org/
2. Run the installer — Windows 10 (1809+) or newer required
3. Use the default installation folder `C:\msys64`
4. When done, click **Finish** — MSYS2 UCRT64 terminal will open

---

## Step 2 — Which Terminal to Use

MSYS2 installs multiple terminals. Use the right one for the right task:

| Terminal | When to use |
|----------|-------------|
| **MSYS2 MSYS** | Installing packages with `pacman` |
| **MSYS2 UCRT64** | Building and running your C++ project |
| **MSYS2 MinGW64** | Avoid — can cause DLL mismatch issues |

> Always install packages in **MSYS2 MSYS**.
> Always build and run code in **MSYS2 UCRT64**.

---

## Step 3 — Install All Required Packages

Open **MSYS2 MSYS** terminal and run each line:

```bash
# Core build tools (g++, gcc, make)
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain

# CMake
pacman -S mingw-w64-ucrt-x86_64-cmake

# Ninja (faster builds)
pacman -S mingw-w64-ucrt-x86_64-ninja

# Clang (for clang-format)
pacman -S mingw-w64-ucrt-x86_64-clang

# Debugger
pacman -S mingw-w64-ucrt-x86_64-gdb

# fmt library (string formatting)
pacman -S mingw-w64-ucrt-x86_64-fmt

pacman -S mingw-w64-ucrt-x86_64-clang-tools-extra
```

---

## Step 4 — Verify Everything Works

Open **MSYS2 UCRT64** terminal and run:

```bash
g++ --version
cmake --version
ninja --version
clang-format --version
gdb --version
```

All commands should return a version number without errors.

---

## Step 5 — Add to Windows PATH (optional but recommended)

So you can use these tools from any terminal (VS Code, Windows Terminal):

1. Open **Start Menu** and search "Environment Variables"
2. Click "Edit the system environment variables"
3. Under **System variables**, select `Path` and click **Edit**
4. Add: `C:\msys64\ucrt64\bin`
5. Make sure it comes before any other MinGW entries
6. Click OK and restart your terminal

---

## Packages to Add Per Phase

Install these when you reach the relevant phase:

```bash
# Phase 5+ — fast matrix operations
pacman -S mingw-w64-ucrt-x86_64-openblas

# Phase 14 — Python bindings
pacman -S mingw-w64-ucrt-x86_64-python
pacman -S mingw-w64-ucrt-x86_64-pybind11

# Phase 15 — Rust FFI
# Install via rustup instead: https://rustup.rs
```

---

## Package Management

```bash
# Install a package
pacman -S <package-name>

# Search for a package
pacman -Ss <keyword>

# Update all installed packages
pacman -Syu

# Remove a package
pacman -R <package-name>

# List installed packages
pacman -Q
```

---

## Quick Reference

| Goal | Command |
|------|---------|
| Install a package | `pacman -S <package>` |
| Update everything | `pacman -Syu` |
| Search packages | `pacman -Ss <keyword>` |
| Check g++ version | `g++ --version` |
| Check cmake version | `cmake --version` |
