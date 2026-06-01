# LLM Systems From Scratch

> **This is an open, educational repository.**
> It is not a software product. It is not a deployable system.
> It is a structured, hands-on learning project — open to everyone.

This repository exists to help **students, engineers, and developers** deeply understand how Large Language Models work — not by using them, but by building every core function and algorithm they depend on, from scratch, in **C++ and Rust**.

No cloud. No APIs. No black boxes. Just code and fundamentals.

---

## Who This Is For

- Students studying machine learning, systems programming, or AI
- Engineers who want to understand what actually happens inside an LLM
- Developers learning C++ or Rust through a meaningful, real-world problem domain
- Anyone curious enough to go deeper than the surface

---

## What This Is Not

- This is **not** a language model
- This is **not** production software
- This is **not** a framework or library meant for deployment
- This is **not** affiliated with any AI company or product

---

## What This Is

A **complete map of every core module an LLM is built on** — implemented one phase at a time, from the lowest level up.

Every phase = one core module. Every module = one concept that a real language model cannot exist without.

By the end, you will have built from scratch:

```
Tensors → Math → Autograd → Neural Layers → Embeddings →
Tokenizer → Positional Encoding → Attention → Transformer →
Normalization → Feed-Forward → Sampling → Inference Engine →
Python Bindings → Rust Memory Layer
```

---

## Language Stack

| Layer | Language | Purpose |
|---|---|---|
| Core engine | C++ | All fundamental algorithms |
| Memory safety layer | Rust (via FFI) | Specific subsystems plugged into C++ |
| Bindings | Python / JavaScript | Expose C++ engine for scripting and web |

> Rust does **not** replace C++. It extends it. Rust is used for specific components — memory management, safe concurrent pipelines, inference serving — and plugged into the C++ engine via FFI (Foreign Function Interface).

---

## Core Modules — Phase by Phase

Each phase introduces one core module. That module is a real, named concept inside a real language model architecture.

---

### Phase 1 — Tensor

**Module: Tensor Operations**
> How LLMs store and compute on data

Everything in a language model is a number in a multidimensional array. This phase builds the foundational data structure.

- N-dimensional array (Tensor class)
- Shape and stride tracking
- Element-wise operations: add, subtract, multiply
- Memory layout (row-major)

---

### Phase 2 — Linear Algebra Engine

**Module: Matrix Multiplication**
> The single most-used operation in all of deep learning

Every layer in a transformer — attention, projection, feed-forward — is a matrix multiplication. This phase builds and optimizes it.

- Naive matrix multiplication (baseline)
- Cache-optimized version (loop tiling)
- Multithreaded version (`std::thread` / OpenMP)

---

### Phase 3 — Autograd

**Module: Automatic Differentiation**
> How models learn — the algorithm behind every weight update

Without autograd, there is no training. This phase builds the computation graph and the backward pass.

- Computation graph (nodes and edges)
- Forward pass execution
- Backward pass — gradient computation via chain rule

---

### Phase 4 — Neural Network Layers

**Module: Layer Functions**
> The building blocks stacked inside every neural network

This phase builds composable, trainable layers on top of tensors and autograd.

- Dense (fully connected) layer
- Activation functions: ReLU, tanh, sigmoid, GELU
- Loss functions: MSE, cross-entropy
- Test: XOR problem, simple classification

---

### Phase 5 — Embeddings

**Module: Embedding Layer**
> How LLMs convert token IDs into meaning

Tokens are integers. Embeddings turn those integers into vectors that carry semantic meaning — this is the first thing a transformer does with its input.

- Embedding table (vocabulary × dimension)
- Lookup operation
- Gradient flow through embeddings

---

### Phase 6 — Tokenizer

**Module: Tokenization**
> How LLMs read text — converting raw strings into token sequences

Language models do not read characters. They read tokens — integer IDs from a fixed vocabulary. This phase builds the algorithm that produces them.

- Whitespace tokenizer (baseline)
- Byte Pair Encoding (BPE) — the core algorithm used in most real tokenizers
- Vocabulary building
- Encode and decode functions

---

### Phase 7 — Positional Encoding

**Module: Positional Encoding**
> How LLMs know the order of tokens

Attention has no built-in sense of position. This phase implements the algorithms that inject order information into the input sequence.

- Sinusoidal positional encoding (original transformer)
- Learned positional embeddings
- Rotary Positional Encoding (RoPE) — used in modern architectures

---

### Phase 8 — Attention

**Module: Attention Mechanism**
> The core algorithm of transformer-based architectures

This is the mechanism that allows a model to relate any token to any other token in a sequence, regardless of distance.

- Q, K, V projections (linear transforms)
- Scaled dot-product attention
- Softmax
- Causal (masked) attention — for autoregressive generation
- Multi-head attention

---

### Phase 9 — Normalization

**Module: Layer Normalization**
> How LLMs stay stable during training and inference

Without normalization, deep networks become numerically unstable. This phase implements the normalization used inside every transformer block.

- Layer normalization (LayerNorm)
- RMS normalization (RMSNorm) — used in modern architectures
- Learnable scale and shift parameters (gamma, beta)

---

### Phase 10 — Feed-Forward Network

**Module: Feed-Forward Block**
> The computation that follows attention in every transformer layer

Every transformer block has two parts: attention and a feed-forward network. This phase builds the FFN.

- Two-layer MLP with activation
- GELU activation function
- Projection in → hidden → projection out
- Role in transformer block (context: runs after attention)

---

### Phase 11 — Transformer Block

**Module: Transformer Block**
> One complete unit of a transformer — assembled from all prior modules

This phase assembles the full transformer block from the components built in previous phases.

- Pre-norm architecture (LayerNorm → Attention → residual)
- Feed-forward sublayer (LayerNorm → FFN → residual)
- Residual connections
- Stacking N blocks into a full transformer backbone

---

### Phase 12 — Sampling & Output Head

**Module: Sampling Algorithms**
> How LLMs decide what token to generate next

After the transformer runs, a probability distribution over the vocabulary is produced. This phase implements the algorithms that select the next token from it.

- Linear projection to vocabulary (logits)
- Softmax to probability distribution
- Greedy decoding
- Temperature scaling
- Top-k sampling
- Top-p (nucleus) sampling

---

### Phase 13 — Inference Engine

**Module: Inference Runtime**
> The execution engine — how a trained model runs efficiently

This phase builds the runtime that loads weights and executes the full forward pass, without any training overhead.

- Weight serialization and loading from file
- Full forward pass pipeline
- KV cache — stores past key/value pairs to avoid recomputation
- Token generation loop (autoregressive decoding)

---

### Phase 14 — Language Bindings

**Module: Python & JavaScript Bindings**
> Exposing the C++ engine to higher-level languages

This phase wraps the C++ engine so it can be used from Python scripts and web environments.

**Python (pybind11):**
```cpp
// C++ side
Tensor matmul(Tensor a, Tensor b);
```
```python
# Python side
import llmsys
llmsys.matmul(a, b)
```

**JavaScript / Web:**
- Compile C++ to WebAssembly (WASM) for in-browser execution
- Or expose a lightweight REST API

---

### Phase 15 — Rust Memory Layer

**Module: Rust FFI Components**
> Precision components in Rust, plugged into the C++ engine

Rust does not replace C++. This phase builds specific subsystems in Rust where its ownership model and memory safety give a concrete advantage — then connects them to the C++ engine via FFI.

- Safe memory allocator (plugged into C++ tensor operations)
- Concurrent data pipeline (safe multithreaded loading)
- Inference server (async, no GC pauses, production-grade serving)
- FFI interface layer between Rust and C++

Explore: [`burn`](https://github.com/tracel-ai/burn), [`candle`](https://github.com/huggingface/candle), [`tch-rs`](https://github.com/LaurentMazare/tch-rs)

---

## Full Module Map

| Phase | Module | Concept in LLM |
|---|---|---|
| 1 | Tensor | Data storage and computation |
| 2 | Matrix Multiplication | Core math operation |
| 3 | Autograd | How models learn |
| 4 | Neural Network Layers | Trainable building blocks |
| 5 | Embeddings | Token → vector conversion |
| 6 | Tokenizer | Text → token IDs |
| 7 | Positional Encoding | Token order awareness |
| 8 | Attention | Token-to-token relationships |
| 9 | Normalization | Training and inference stability |
| 10 | Feed-Forward Network | Per-token computation after attention |
| 11 | Transformer Block | Full assembled unit |
| 12 | Sampling & Output Head | Next-token selection |
| 13 | Inference Engine | Runtime execution |
| 14 | Language Bindings | Python / JS interface |
| 15 | Rust Memory Layer | Safe, high-performance components via FFI |

---

## Open Collaboration

This repository is **open for collaboration**. Everyone is welcome to contribute — whether you are a student, a researcher, a hobbyist, or a professional engineer.

Ways to contribute:

- Implement a module in a phase
- Write tests for an existing implementation
- Improve documentation or add explanations
- Add alternative implementations (different algorithms, different approaches)
- Fix bugs or improve performance

Please read [CONTRIBUTING.md](./CONTRIBUTING.md) before opening a pull request.
Please read [CODE_OF_CONDUCT.md](./CODE_OF_CONDUCT.md) for community standards.

---

## Requirements

- C++17 or later
- Rust (stable toolchain) — for Phase 15
- No cloud accounts required
- No paid APIs required
- No GPU required (CPU-only by design for learning purposes)

---

## License

MIT — free to use, study, fork, and build upon.

---

## A Note on Purpose

This project exists because understanding AI at the source level matters.

The goal is not to compete with existing frameworks. The goal is to make the internals legible — so that anyone who works through these phases comes away with a genuine understanding of what a language model is made of, one algorithm at a time.
