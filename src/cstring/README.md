# Custom C-Style String Library in C++

This repository contains a **custom implementation of C-style string functions** in C++, similar to the standard `<cstring>` library.  
All functions operate on **null-terminated strings** and are implemented from scratch using pointer and index manipulation.

---

## Functions Overview

| Function | Description | Example |
|----------|-------------|---------|
| `Strlen` | Returns the length of a string (excluding null terminator). | `size_t len = Strlen("hello"); // 5` |
| `Strcmp` | Lexicographically compares two strings. Returns `<0`, `0`, `>0`. | `int cmp = Strcmp("abc","abd"); // -1` |
| `Strncmp` | Compares the first `count` characters of two strings. | `int cmp = Strncmp("abc","abd",2); // 0` |
| `Strchr` | Returns pointer to the first occurrence of a character in a string, or `nullptr` if not found. | `const char* p = Strchr("hello",'l');` |
| `Strrchr` | Returns pointer to the last occurrence of a character in a string, or `nullptr`. | `const char* p = Strrchr("hello",'l');` |
| `Strspn` | Returns length of initial segment of `dest` consisting entirely of characters from `src`. | `size_t n = Strspn("abcde","abc"); // 3` |
| `Strcspn` | Returns length of initial segment of `dest` consisting of characters **not** in `src`. | `size_t n = Strcspn("abcde","de"); // 3` |
| `Strpbrk` | Returns pointer to first character in `dest` that is in `breakset`, or `nullptr`. | `const char* p = Strpbrk("abcde","xzcd"); // 'c'` |
| `Strstr` | Returns pointer to first occurrence of `pattern` in `str`, or `nullptr`. | `const char* p = Strstr("hello world","world");` |
| `Strcpy` | Copies `src` (including null terminator) into `dest`. Returns `dest`. | `char buf[10]; Strcpy(buf,"hi");` |
| `Strncpy` | Copies exactly `count` characters from `src` to `dest`. Pads with nulls if `count` exceeds `src` length. Returns `dest`. | `char buf[5]; Strncpy(buf,"abc",5); // buf = "abc\0\0"` |
| `Strcat` | Appends `src` to the end of `dest`. Returns `dest`. | `char buf[10] = "hi"; Strcat(buf," there"); // "hi there"` |
| `Strncat` | Appends first `count` characters of `src` to `dest` with null terminator. If `count` > `src` length, works like `Strcat`. | `char buf[10] = "hi"; Strncat(buf," there",3); // "hi th"` |

---

## Usage

1. Include the header:

```cpp
#include "cstring.hpp"

2. Call the functions with C-style strings:

char buf[20];

Strcpy(buf, "hello");
Strcat(buf, " world");
size_t len = Strlen(buf); // 11

const char* p = Strchr(buf, 'w'); // points to 'w' in "world"

Features

Reimplementation of classic C string operations using raw pointers and indices.
Handles null-terminated strings safely.
Supports partial operations (Strncpy, Strncat, Strncmp) and search operations (Strchr, Strrchr, Strpbrk, Strstr).
Designed for educational purposes, learning pointer arithmetic, and low-level string handling.

License
MIT License — free to use, modify, and distribute.
