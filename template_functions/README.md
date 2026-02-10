# Template Sequence Utilities for C++

A collection of **C++ template functions** for working with sequences (arrays, pointers, or contiguous containers).  
These utilities implement common algorithms found in the STL, with pointer-based generic programming for learning and practical use.

---

## Functions Overview

| Function | Description | Example |
|----------|-------------|---------|
| `IsSortedUntil` | Returns a pointer to the first element that breaks non-decreasing order in a sequence. | `int a[]{1,2,2,3,4}; auto p = IsSortedUntil(a, a+5);` |
| `Unique` | Removes duplicates from a non-decreasing sequence, moving unique elements to the front. Returns new end pointer. | `int a[]{1,2,2,3}; auto p = Unique(a, a+4);` |
| `Copy` | Copies `[src_begin, src_end)` to `dest`. Returns pointer to element after last copied. | `Copy(src, src+3, dest);` |
| `CopyBackward` | Copies `[src_begin, src_end)` into `dest_end` in reverse order safely for overlapping ranges. Returns `dest_end`. | `CopyBackward(src, src+3, dest+3);` |
| `Reverse` | Reverses elements in `[begin, end)`. | `Reverse(a, a+5);` |
| `Rotate` | Cyclically rotates `[begin, mid)` and `[mid, end)`. | `Rotate(a, a+2, a+5);` |
| `Remove` | Removes all occurrences of `value` from `[begin, end)`. Returns new end pointer. | `Remove(a, a+5, 2);` |
| `BinarySearch` | Checks if `value` exists in sorted `[begin, end)` using only `<` comparison. | `BinarySearch(a, a+5, 3);` |
| `LowerBound` | Returns pointer to first element `>= value` in sorted `[begin, end)`. | `LowerBound(a, a+5, 3);` |
| `UpperBound` | Returns pointer to first element `> value` in sorted `[begin, end)`. | `UpperBound(a, a+5, 3);` |
| `Merge` | Merges two sorted sequences into one sorted output sequence. Returns pointer to end of merged sequence. | `Merge(first, first+2, second, second+3, out);` |

---

## Usage

1. Include the required header files in your project:
```cpp
#include "IsSortedUntil.hpp"
#include "Unique.hpp"
#include "Copy.hpp"
#include "ReverseRotate.hpp"
#include "Remove.hpp"
#include "BinaryLowerUpper.hpp"
#include "Merge.hpp"

2. Call functions with pointers to sequences:
int arr[]{1,2,2,3,4,4};
auto new_end = Unique(arr, arr + 6); // arr = {1,2,3,4,...}, new_end points to arr+4

Features

Template-based — works with any type that supports assignment and < comparison.
Pointer-based — compatible with raw arrays, contiguous containers, and pointer arithmetic.
Linear-time algorithms wherever possible.
Safe copying with CopyBackward for overlapping ranges.
STL-style return values — functions return pointers to ends of resulting sequences for chaining.
