Complex Number Class (C++)

📌 Overview

This project implements a custom "Complex" number class in C++, providing a full set of arithmetic operations, comparisons, and utility functions. The implementation is designed to mimic the behavior of standard complex number libraries while maintaining strict control over floating-point precision and operator semantics.

The class supports both "Complex"-to-"Complex" and "Complex"-to-"double" interactions, making it flexible for numerical computations, simulations, and algorithmic tasks.

---

🎯 Problem Statement

Standard libraries (such as "std::complex") are often treated as black boxes. The goal of this project is to:

- Reimplement complex number arithmetic from scratch
- Ensure numerical stability when working with floating-point values
- Provide a clean and predictable operator interface
- Handle edge cases such as division by zero
- Maintain symmetry of operations ("a + b == b + a" where applicable)

This task is commonly used in technical interviews to evaluate:

- Operator overloading skills
- Understanding of floating-point precision
- API design in C++
- Code correctness and robustness

---

⚙️ Features

✔ Core Functionality

- Real and imaginary parts access ("Real()", "Imag()")
- Magnitude calculation ("Abs()")
- Safe division with zero-check

✔ Arithmetic Operations

Supports full arithmetic with:

- "Complex + Complex"
- "Complex - Complex"
- "Complex * Complex"
- "Complex / Complex"

And mixed operations:

- "Complex + double"
- "double + Complex"
- (same for "-", "*", "/")

✔ Operator Overloading

- Compound operators: "+=", "-=", "*=", "/="
- Unary operators: "+", "-"
- Comparison operators: "==", "!=" (with EPS tolerance)

✔ Numerical Stability

Floating-point comparisons use an epsilon:

static constexpr double EPS = 1e-12;

This avoids incorrect equality results due to precision errors.

---

🧮 Mathematical Model

A complex number is defined as:

z = a + bi

Where:

- "a" — real part
- "b" — imaginary part
- "i² = -1"

Multiplication

(a + bi)(c + di) = (ac - bd) + (ad + bc)i

Division

(a + bi) / (c + di) =
[(ac + bd) + (bc - ad)i] / (c² + d²)

---

🚀 Usage Example

#include "Complex.hpp"
#include <iostream>

int main() {
    Complex a(3, 4);
    Complex b(1, -2);

    Complex sum = a + b;
    Complex product = a * b;
    Complex quotient = a / b;

    std::cout << "Abs(a) = " << a.Abs() << std::endl;

    if (a != b) {
        std::cout << "Numbers are different\n";
    }

    return 0;
}

---

⚠️ Error Handling

Division by zero is explicitly checked:

if (std::abs(d) < EPS) {
    throw std::invalid_argument("Division by zero");
}

---

🏗 Design Decisions

- Pass-by-value for lhs in operators → enables chaining and reuse of compound operators
- EPS-based comparison → avoids floating-point pitfalls
- Explicit constructor → prevents unintended implicit conversions
- Symmetric operator support → consistent mathematical behavior


👤 Author

Self-implemented as part of C++ practice and interview preparation.
