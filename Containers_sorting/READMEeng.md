# Containers Sorting (C++)

# Problem statement

A warehouse stores containers with N different types of goods. These containers are arranged in N stacks. Each stack can contain containers of any type of goods (the stack may initially be empty).

A forklift can take the top container from any stack and place it on top of any stack.

All containers containing the first type of goods must be placed in the first stack, those containing the second type in the second stack, and so on.

The program must display the sequence of forklift actions or a message indicating that the problem is unsolvable.

Input Format
The first line of the input data contains a single natural number N, not exceeding 500.

The next N lines describe the stacks of containers: first, ki is the number of containers in the stack.
Then, ki numbers represent the types of goods in the containers in the stack, from bottom to top.
Each stack initially contains no more than 500 containers (this limitation may be exceeded during container movement).

Output format
The program should output a description of the forklift's actions:
- for each action, print two numbers—which stack to take the container from and which stack to place it in. Note that minimizing the number of forklift operations is not required.

If the problem has no solution, a single number, 0, should be output.

Example
Input:
3
4 1 2 3 2
0
0
Output:
1 2
1 3
1 2

Example explanation:

Initially, the first stack contains four containers: the bottom one contains the first type of product, the top one contains the second type of product, the top one contains the third type of product, and the top one contains another type of product.
The second and third stacks are empty.

## Overview

This project implements a deterministic container redistribution engine for a warehouse system.

There are:

- N container types
- N stacks
- Each stack may initially contain containers of any type
- A forklift can move only the top container from one stack to another

### Objective

Rearrange containers so that:

- Stack 1 contains only type 1
- Stack 2 contains only type 2
- ...
- Stack N contains only type N

The program outputs the sequence of forklift operations required to achieve the target state.

Minimizing operations is NOT required.
If redistribution is impossible — output 0.

---

## Core Engineering Decisions

### Data Structure

Custom stack implementation using a singly linked list:

- O(1) push
- O(1) pop
- Manual memory management
- No STL containers used (intentional low-level control)

### Why Not STL?

This project intentionally avoids std::stack to demonstrate:

- pointer-level memory management
- linked list implementation
- understanding of stack mechanics
- deterministic resource cleanup

---

## Algorithm Strategy

### Case N > 2

1. Read input.
2. Ignore containers already correctly placed at bottom.
3. Process stacks sequentially.
4. If target stack is empty → direct move.
5. If target stack is not empty → use stack N as temporary buffer.
6. After processing all stacks, flush the buffer.

### Case N == 2

Special validation logic is applied.
If invalid ordering detected → output 0.

---

## Complexity

| Metric | Value |
|--------|--------|
| Time   | O(M) |
| Space  | O(M) |

M = total number of containers.

---

## Memory Safety

- Explicit new / delete
- Dedicated Clear() function
- No memory leaks
- Suitable for Valgrind verification

---

## Build

g++ main.cpp -O2 -std=c++17 -Wall -Wextra -pedantic -o warehouse


## 📁 Suggested Project Structure

warehouse-sort/ │ ├── src/ │   └── main.cpp │ ├── tests/ │   ├── test1.txt │   ├── test2.txt │   └── test3.txt │ ├── .github/ │   └── workflows/ │       └── build.yml │ └── README.md

---

## 🧪 Example Test Cases

### `tests/test1.txt`

3 4 1 2 3 2 0 0

Expected: non-zero output.

---

### `tests/test2.txt`

2 3 1 2 1 0

Expected:

0

---

### `tests/test3.txt`

3 0 0 0

Expected: no output (already sorted).

---

# ⚙️ GitHub Actions CI

Create file:

.github/workflows/build.yml

### `build.yml`

yaml
name: C++ Build and Test

on:
  push:
  pull_request:

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4

      - name: Install compiler
        run: sudo apt update && sudo apt install -y g++

      - name: Build
        run: |
          g++ src/main.cpp -O2 -std=c++17 -Wall -Wextra -pedantic -o warehouse

      - name: Run tests
        run: |
          for file in tests/*.txt; do
            echo "Running $file"
            ./warehouse < $file > output.txt
          done
