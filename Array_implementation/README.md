Array — C++ Template Wrapper over C-Style Arrays

📌 Overview

This project implements a simplified analogue of "std::array" in C++. The goal is to create a lightweight, efficient wrapper over a C-style array while preserving its performance characteristics and improving usability through an object-oriented interface.

---

🎯 Objectives

- Eliminate common drawbacks of C-style arrays:
  - implicit decay to pointers
  - loss of size information when passed to functions (array-to-pointer decay)
  - lack of support for copying and assignment (no value semantics)
- Preserve advantages:
  - fixed size known at compile time
  - stack allocation
  - memory locality and performance

---

🧱 Class Specification

Template Parameters

template <class T, size_t N>
class Array;

- "T" — type of elements
- "N" — number of elements (fixed at compile time)

---

⚠️ Key Constraint

The class must contain exactly one field, and it must be public:

T data[N];

This enables aggregate initialization:

Array<int, 4> arr{1, 2, 3}; // → {1, 2, 3, 0}

---

⚙️ Implemented Interface

🔹 Element Access

- "T& operator[](size_t index)"

- "const T& operator[](size_t index) const"

- "T& Front()"

- "const T& Front() const"

- "T& Back()"

- "const T& Back() const"

---

🔹 Data Access

- "T* Data()"
- "const T* Data() const"

Returns pointer to underlying array.

---

🔹 Capacity

- "size_t Size() const"
  Returns number of elements ("N")

- "bool Empty() const"
  Returns "true" if "N == 0"

---

🔹 Modifiers

- "void Fill(const T& value)"
  Fills entire array with "value"

- "void Swap(Array<T, N>& other)"
  Swaps contents with another array of same size

---

🧠 Additional Task: Array Traits

Implemented via template overloading.

---

🔹 "GetSize(array)"

Returns:

- number of elements for C-style array
- "0" for non-array types

int a[3];
GetSize(a); // 3

int x;
GetSize(x); // 0

---

🔹 "GetRank(array)"

Returns number of dimensions:

int b[3][2][1];
GetRank(b); // 3

---

🔹 "GetNumElements(array)"

Returns total number of elements:

int b[3][2][1];
GetNumElements(b); // 6

---

🔁 Implementation Approach

Recursion over types

- Base case:
  
  - non-array → rank = 0, elements = 1

- Recursive case:
  
  - array "T[N]":
    - "rank = 1 + GetRank(T)"
    - "elements = N * GetNumElements(T)"

---

🧪 Examples

int x;
int a[3];
int b[3][2][1];

GetSize(x); // 0
GetSize(a); // 3
GetSize(b); // 3

GetRank(x); // 0
GetRank(a); // 1
GetRank(b); // 3

GetNumElements(x); // 1
GetNumElements(a); // 3
GetNumElements(b); // 6

---

📁 Project Structure

array.hpp   // single header with full implementation

---

⚙️ Build & Requirements

- C++17 (or later recommended)
- Clang / GCC compatible

---

🚫 Constraints

- No dynamic memory
- No additional fields in class
- Exact method signatures must be preserved
- Solution must be in a single header file

---

📌 Notes

- The implementation mirrors the design philosophy of "std::array"
- Emphasis is on compile-time behavior and zero-overhead abstraction
- Template overloading is used instead of type traits (for learning purposes)
