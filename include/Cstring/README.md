# Custom String Utilities in C++

This repository contains a collection of **custom C++ string functions**, implemented similarly to the standard C string library (`<cstring>`), but written from scratch for learning and practical purposes.  
All functions operate on **null-terminated C-style strings** and use pointer-based manipulation.

---

## Functions Overview

| Function | Description | Example |
|----------|-------------|---------|
| `Strlen` | Returns the length of a null-terminated string (excluding the null character). | `size_t len = Strlen("hello"); // 5` |
| `Strcmp` | Lexicographically compares two strings. Returns `<0`, `0`, or `>0`. | `int cmp = Strcmp("abc","abd"); // <0` |
| `Strncmp` | Lexicographically compares the first `count` characters of two strings. Stops early if a null character is found. | `int cmp = Strncmp("abc","abd",2); // 0` |
| `Strchr` | Returns a pointer to the first occurrence of a character in a string, including null terminator. Returns `nullptr` if not found. | `const char* p = Strchr("hello",'l'); // points to first 'l'` |
| `Strrchr` | Returns a pointer to the last occurrence of a character in a string, including null terminator. Returns `nullptr` if not found. | `const char* p = Strrchr("hello",'l'); // points to second 'l'` |
| `Strspn` | Returns the length of the initial segment of `dest` consisting entirely of characters in `src`. | `size_t n = Strspn("abcde","abc"); // 3` |
| `Strcspn` | Returns the length of the initial segment of `dest` consisting of characters **not** in `src`. | `size_t n = Strcspn("abcde","de"); // 3` |
| `Strpbrk` | Returns a pointer to the first character in `dest` that is also in `breakset`, or `nullptr` if none. | `const char* p = Strpbrk("abcde","xzcd"); // points to 'c'` |
| `Strstr` | Returns a pointer to the first occurrence of substring `pattern` in `str`, or `nullptr` if not found. | `const char* p = Strstr("hello world","world");` |
| `Strcpy` | Copies `src` (including null terminator) into `dest`. Returns `dest`. | `char buf[10]; Strcpy(buf,"hi");` |
| `Strncpy` | Copies exactly `count` characters from `src` to `dest`. Pads with nulls if `count` exceeds `src` length. Returns `dest`. | `char buf[5]; Strncpy(buf,"abc",5); // buf = "abc\0\0"` |
| `Strcat` | Appends `src` to the end of `dest`. Returns `dest`. | `char buf[10] = "hi"; Strcat(buf," there"); // buf = "hi there"` |
| `Strncat` | Appends the first `count` characters of `src` to `dest`, ensuring null terminator. Returns `dest`. | `char buf[10] = "hi"; Strncat(buf," there",3); // buf = "hi th"` |

---

## Usage

1. Include the header in your project:

```cpp
#include "cstring.hpp"

Call the functions with C-style strings:

char buf[20];

Strcpy(buf, "hello");
Strcat(buf, " world");
size_t len = Strlen(buf); // 11

Features

Implements classic C string operations using raw pointers.
Handles null-terminated strings safely.
Functions are STL-independent, lightweight, and educational.
Supports partial operations (Strncpy, Strncat, Strncmp) and search operations (Strchr, Strrchr, Strpbrk, Strstr).

