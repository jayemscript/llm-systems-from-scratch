# Phase 1 — Tensor Module

> Goal: Build a minimal, clean tensor library in C++ that every phase after this depends on.
> No code in this file — just what it is, why it exists, how it's structured, and how to build and test it.

---

## What is a Tensor?

A tensor is a multi-dimensional array of numbers with shape information attached.

| Dimensions | What it is | Example |
|---|---|---|
| 0D | A single number (scalar) | `3.14` |
| 1D | A list of numbers (vector) | `[1, 2, 3]` |
| 2D | A grid of numbers (matrix) | `[[1, 2], [3, 4]]` |
| 3D+ | Stacked grids | A batch of sequences, images, etc. |

In memory, a tensor is always a **flat array of floats** — no matter how many dimensions it has. The shape tells you how to interpret that flat array.

Example: a 2x3 tensor with shape `{2, 3}` stores 6 floats in a single flat array:
```
data = [1, 2, 3, 4, 5, 6]
shape = {2, 3}

Interpreted as:
[[1, 2, 3],
 [4, 5, 6]]
```

---

## Why Tensors?

Every single LLM operation is just numbers in arrays being transformed:

- Weight matrices in neural network layers -> 2D tensors
- Token embeddings -> 2D tensors (vocab size x embed dim)
- Attention scores -> 3D tensors (batch x heads x sequence)
- Layer outputs, gradients, activations -> all tensors

Without a tensor type, every phase would manually manage raw arrays, track sizes separately, and have no consistent interface. The tensor module is the foundation everything else is built on.

---

## When is This Used?

Every phase after Phase 1 uses tensors:

- Phase 2 (matmul) — multiplies two 2D tensors
- Phase 3 (autograd) — stores gradients as tensors
- Phase 4 (layers) — weights and outputs are tensors
- Phase 5 (embeddings) — lookup table stored as a 2D tensor
- Phase 8 (attention) — scores and context are tensors
- And so on

Build this correctly once, and it carries the whole project.

---

## What Should the Tensor Do? (The API)

### Core Data (what every tensor stores)
- A flat array of `float` values
- A `shape` vector — e.g., `{2, 3}` means 2 rows, 3 columns
- A `size` — total number of elements (product of all shape values)
- A `rank` — number of dimensions (length of the shape vector)

### Construction
- Create a tensor from a shape, filled with zeros by default
- Create a tensor from a shape + existing data vector
- Create a tensor filled with zeros
- Create a tensor filled with ones
- Create a tensor filled with a constant value
- Create a tensor with random values (needed for initializing weights later)

### Data Access
- Get a value by multi-dimensional index — e.g., `tensor.at({1, 2})`
- Set a value by multi-dimensional index — e.g., `tensor.set({1, 2}, 5.0f)`
- Get a raw pointer to the underlying data (needed by matmul in Phase 2)

### Element-wise Operations
- Add two tensors (same shape, element by element)
- Subtract two tensors
- Multiply two tensors element-wise (not matrix multiply — that is Phase 2)
- Divide two tensors element-wise
- Scale a tensor by a scalar (multiply every element by one number)

### Utility
- Reshape — change shape without changing data
- Get total size
- Get shape

### Printing / Logging
- Print the tensor in a readable, formatted way
- Print shape and rank
- Print raw flat data

---

## What the Tensor Does NOT Do in Phase 1

These come in later phases:

- Matrix multiplication -> Phase 2
- Gradient tracking -> Phase 3
- GPU support -> far future
- Broadcasting (like NumPy) -> can be added later
- Slicing / indexing ranges -> not needed yet

---

## File Structure Inside `src/tensor/`

This module is split into three concerns — same idea as splitting a NestJS service into service, controller, and types.

```
src/tensor/
├── tensor.h            // The Tensor class — data, shape, access
├── tensor.cpp
├── tensor_ops.h        // Operations — add, subtract, multiply, fill, zeros, ones, random
├── tensor_ops.cpp
├── tensor_print.h      // Printing and logging — human-readable output for testing
└── tensor_print.cpp
```

And the entry point for running and manually testing:

```
examples/
└── run_tensor.cpp      // main() — creates tensors, runs ops, prints output
```

---

## What Each File is Responsible For

### `tensor.h` and `tensor.cpp`
The core class. Declares and implements the `Tensor` class.

Contains:
- Member variables: `data_` (flat float array), `shape_`, `size_`, `rank_`
- Constructors — from shape, from shape + data
- Access methods — `at()`, `set()`, `data()` raw pointer
- `reshape()`

Does NOT contain operations or printing. Those are separate concerns.

### `tensor_ops.h` and `tensor_ops.cpp`
Free functions that operate on tensors. Does not need to be a class — just functions.

Contains:
- `add(a, b)` -> returns new tensor
- `subtract(a, b)` -> returns new tensor
- `multiply(a, b)` -> element-wise, returns new tensor
- `divide(a, b)` -> returns new tensor
- `scale(a, scalar)` -> returns new tensor
- `zeros(shape)` -> returns tensor filled with 0
- `ones(shape)` -> returns tensor filled with 1
- `fill(shape, value)` -> returns tensor filled with value
- `rand_uniform(shape)` -> returns tensor with random floats

### `tensor_print.h` and `tensor_print.cpp`
Everything related to displaying a tensor. Kept separate so you can use the tensor and ops without pulling in print logic.

Contains:
- `print_tensor(t)` — prints values formatted by shape (row by row for 2D)
- `print_shape(t)` — prints shape vector
- `print_flat(t)` — prints raw flat data array

### `examples/run_tensor.cpp`
This is the only file with a `main()` function in Phase 1. This is what you actually run to verify everything works.

It will:
1. Create tensors of different shapes
2. Print them
3. Run operations
4. Print results
5. You read the terminal output and verify it looks correct

This is your manual test. Every operation you implement gets exercised here.

---

## Why No `main.cpp` in `src/tensor/`?

Because `src/tensor/` is a library, not a program. It has no entry point by itself.

The analogy from backend engineering: `src/tensor/` is like an npm package. It does not run on its own. `examples/run_tensor.cpp` is the app that imports and runs it.

As phases are added, each phase gets its own `examples/run_*.cpp` entry point.

---

## How CMake Sees This

`CMakeLists.txt` at the root defines:

1. A library target for the tensor module:
```
add_library(tensor
    src/tensor/tensor.cpp
    src/tensor/tensor_ops.cpp
    src/tensor/tensor_print.cpp
)
```

2. An executable target for the example / manual test:
```
add_executable(run_tensor examples/run_tensor.cpp)
target_link_libraries(run_tensor PRIVATE tensor)
```

When you build, CMake compiles both. You run the executable to see output.

---

## How to Build and Run (MSYS2 UCRT64 + Ninja)

```bash
# Step 1 — configure (only need to do this once, or after changing CMakeLists.txt)
cmake -B build -G Ninja

# Step 2 — compile
cmake --build build

# Step 3 — run the manual test
./build/run_tensor.exe
```

You will see printed output in the terminal. That is how you know it works.

---

## What the Output Will Look Like

When `run_tensor.cpp` runs, the terminal output should look something like:

```
[Tensor] shape: {2, 3}  rank: 2  size: 6
[[1.00, 2.00, 3.00],
 [4.00, 5.00, 6.00]]

[zeros] shape: {2, 3}
[[0.00, 0.00, 0.00],
 [0.00, 0.00, 0.00]]

[add result] shape: {2, 3}
[[2.00, 4.00, 6.00],
 [8.00, 10.00, 12.00]]
```

Every operation prints a label, the shape, and the values. You read this and verify correctness manually.

---

## Build Order for Phase 1

Do these one step at a time, in order:

1. Write `tensor.h` — just the class declaration, no implementation
2. Write `tensor.cpp` — implement constructors and access methods
3. Wire up `CMakeLists.txt` so it compiles
4. Write `tensor_print.h` and `tensor_print.cpp` — implement `print_tensor`
5. Write a minimal `run_tensor.cpp` with `main()` — create one tensor, print it, verify it compiles and runs
6. Write `tensor_ops.h` and `tensor_ops.cpp` — implement all operations
7. Expand `run_tensor.cpp` to test every operation
8. Verify all output looks correct

---

## Summary

| Question | Answer |
|---|---|
| What is a tensor? | A flat float array plus shape information |
| Why build this? | It is the data structure every other phase depends on |
| How many files? | 6 source files + 1 example entry point |
| How to run? | `cmake --build build` then `./build/run_tensor.exe` |
| How to test? | Read the printed terminal output in `run_tensor.cpp` |
| Is it modular? | Yes — class, ops, and print are split by concern |
| What does NOT go here? | Matmul, gradients, GPU, broadcasting |