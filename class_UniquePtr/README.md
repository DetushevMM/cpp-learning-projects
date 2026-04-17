# UniquePtr

A minimal educational implementation of a **unique-ownership smart pointer** in C++11, modeled after [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr).

Smart pointers follow the **RAII** idiom: resource lifetime is tied to object lifetime, so memory (and other resources) are released in the destructor without manual `delete`.

## About this project

This repository contains a **course / homework assignment**: a single-header template `UniquePtr` that mimics the core behavior of `std::unique_ptr`—non-copyable, movable, and zero-overhead in typical use compared to raw pointers, with safer ownership semantics.

## API

Implemented in **`unique_ptr.hpp`**:

| Feature | Description |
|--------|-------------|
| Default constructor | Null pointer |
| `explicit UniquePtr(T*)` | Takes ownership of a raw pointer |
| Copy | Deleted (`= delete`) |
| Move constructor / move assignment | Transfers ownership |
| `Release()` | Relinquishes ownership and returns the raw pointer |
| `Reset(T* = nullptr)` | Replaces the owned pointer; previous resource is deleted |
| `Swap(UniquePtr&)` | Exchanges owned pointers |
| `Get()` | Raw pointer (non-owning view) |
| `operator*` / `operator->` | Dereference |
| `explicit operator bool()` | Tests for non-null |

### Optional: `MakeUnique`

If implemented, a template **`MakeUnique`** forwards constructor arguments to `new T(...)` and returns `UniquePtr<T>`. When present, the header defines **`MAKE_UNIQUE_IMPLEMENTED`**.

## Requirements

- **C++11** or newer  
- Single file: **`unique_ptr.hpp`**

## Usage

```cpp
#include "unique_ptr.hpp"

UniquePtr<int> p(new int(42));
// If MakeUnique is implemented:
// auto p = MakeUnique<int>(42);
```

## Disclaimer

This code is submitted as **educational work**. It is not a substitute for the standard library and is not intended for production without review.

## License

This is free and unencumbered software released into the **public domain**.
