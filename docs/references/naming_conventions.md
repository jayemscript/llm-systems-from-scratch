# Naming Conventions

This project follows standard C++ naming conventions.
All contributors should follow this guide to keep the codebase consistent.

---

## Files

| Type | Convention | Example |
|------|-----------|---------|
| Source files | `snake_case` | `tensor.cpp`, `matrix_mul.cpp` |
| Header files | `snake_case` | `tensor.h`, `matrix_mul.h` |
| Test files | `test_` prefix | `test_tensor.cpp` |

---

## Variables

Use `snake_case` for all variables.

```cpp
int batch_size = 32;
float learning_rate = 0.001f;
std::string model_name = "transformer";
```

---

## Constants and Macros

Use `SCREAMING_SNAKE_CASE` for constants and macros.

```cpp
const int MAX_BATCH_SIZE = 128;
const float DEFAULT_LEARNING_RATE = 0.001f;

#define TENSOR_DEBUG 1
```

---

## Functions

Use `snake_case` for all functions.

```cpp
void print_tensor();
float compute_loss();
int get_batch_size();
```

---

## Classes and Structs

Use `PascalCase` for classes and structs.

```cpp
class TensorLayer {};
class MultiHeadAttention {};
struct LayerConfig {};
```

---

## Class Members

Private members use a trailing underscore `_`.
Public members use plain `snake_case`.

```cpp
class Tensor {
public:
    int num_dims;           // public — no underscore

private:
    float* data_;           // private — trailing underscore
    int shape_[4];
    bool is_allocated_;
};
```

---

## Methods

Use `snake_case`, same as functions.

```cpp
class Tensor {
public:
    void reshape(int rows, int cols);
    float get_value(int index);
    bool is_empty();
};
```

---

## Namespaces

Use `snake_case`, all lowercase.

```cpp
namespace llm_systems {}
namespace tensor_ops {}
```

---

## Template Parameters

Use a single uppercase letter or `PascalCase`.

```cpp
template <typename T>
template <typename DataType>
```

---

## Enums

Enum type in `PascalCase`, values in `SCREAMING_SNAKE_CASE`.

```cpp
enum class ActivationType {
    RELU,
    SIGMOID,
    SOFTMAX
};
```

---

## Quick Reference

| Category | Convention | Example |
|----------|-----------|---------|
| Files | `snake_case` | `tensor_ops.cpp` |
| Variables | `snake_case` | `batch_size` |
| Constants | `SCREAMING_SNAKE_CASE` | `MAX_SEQ_LEN` |
| Functions | `snake_case` | `compute_loss()` |
| Classes | `PascalCase` | `TensorLayer` |
| Private members | `snake_case_` | `data_` |
| Namespaces | `snake_case` | `tensor_ops` |
| Enums (type) | `PascalCase` | `ActivationType` |
| Enums (values) | `SCREAMING_SNAKE_CASE` | `RELU` |
| Template params | Single letter or `PascalCase` | `T`, `DataType` |