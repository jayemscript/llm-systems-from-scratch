# File Structure

> This structure is a living document — it will evolve as the project grows.
> Folders are added per phase. Nothing here is final.

---

```
llm-systems-from-scratch/
│
├── .github/                        # GitHub-specific configs
│   ├── workflows/                  # CI/CD pipelines (GitHub Actions)
│   └── ISSUE_TEMPLATE/             # Issue templates for contributors
│
├── configs/                        # Build and project configuration files
│   ├── cmake/                      # CMake modules and helpers
│   └── rust/                       # Cargo workspace config
│
├── scripts/                        # Utility and automation scripts
│   ├── build.sh                    # Build the C++ project
│   ├── test.sh                     # Run all tests
│   └── format.sh                   # Run clang-format / rustfmt
│
├── src/                            # All source code — one folder per phase/module
│   ├── tensor/                     # Phase 1 — Tensor
│   ├── matmul/                     # Phase 2 — Matrix Multiplication
│   ├── autograd/                   # Phase 3 — Automatic Differentiation
│   ├── layers/                     # Phase 4 — Neural Network Layers
│   ├── embeddings/                 # Phase 5 — Embedding Layer
│   ├── tokenizer/                  # Phase 6 — Tokenizer (BPE)
│   ├── positional_encoding/        # Phase 7 — Positional Encoding
│   ├── attention/                  # Phase 8 — Attention Mechanism
│   ├── normalization/              # Phase 9 — Layer / RMS Normalization
│   ├── feedforward/                # Phase 10 — Feed-Forward Network
│   ├── transformer/                # Phase 11 — Transformer Block
│   ├── sampling/                   # Phase 12 — Sampling & Output Head
│   ├── inference/                  # Phase 13 — Inference Engine
│   ├── bindings/                   # Phase 14 — Python / JS Bindings
│   │   ├── python/                 # pybind11 wrappers
│   │   └── wasm/                   # WebAssembly / JS interface
│   └── rust_layer/                 # Phase 15 — Rust FFI Components
│
├── tests/                          # All tests — mirrors src/ structure
│   ├── tensor/
│   ├── matmul/
│   ├── autograd/
│   ├── layers/
│   ├── embeddings/
│   ├── tokenizer/
│   ├── attention/
│   ├── transformer/
│   └── inference/
│
├── docs/                           # Documentation and learning notes
│   ├── phases/                     # Per-phase explanations and math notes
│   └── references/                 # Papers, links, reading list
│
├── examples/                       # Minimal runnable examples per module
│   ├── run_tensor.cpp
│   ├── run_tokenizer.cpp
│   └── run_attention.cpp
│
├── .gitignore
├── CMakeLists.txt                  # Top-level C++ build file
├── Cargo.toml                      # Rust workspace (Phase 15+)
├── CODE_OF_CONDUCT.md
├── CONTRIBUTING.md
├── FILE_STRUCTURE.md
├── LICENSE
├── README.md
└── SECURITY.md
```

---

## Notes

- `src/` follows the phase order from `README.md` — one folder per module
- `tests/` mirrors `src/` so every module has a corresponding test folder
- `docs/phases/` is where contributors can add explanations, diagrams, and math notes per module
- `examples/` contains the simplest possible runnable demo for each module — no setup required
- `configs/` and `scripts/` keep the root clean
- `.github/workflows/` handles CI — compile check, run tests, format check

---

## Planned Additions

These folders are not created yet but will be added later:

```
docker/                             # Docker and container setup
benchmarks/                         # Performance benchmarks per module
notebooks/                          # Python notebooks for visual walkthroughs
```