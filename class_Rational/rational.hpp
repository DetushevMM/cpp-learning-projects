#pragma once
#include <exception>
#include <iostream>

class RationalDivisionByZero : public std::exception {
public:
    const char* what() const noexcept override;
};

class Rational {
private:
    int numerator_;
    int denominator_;

    int GCD(int a, int b);
    void Normalize();

public:
    Rational();
    Rational(int numerator);                  // NOLINT
    Rational(int numerator, int denominator);

    int GetNumerator() const;
    int GetDenominator() const;

    void SetNumerator(int numerator);
    void SetDenominator(int denominator);     // NOLINT

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational operator+() const;
    Rational operator-() const;

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator!=(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend bool operator>(const Rational& lhs, const Rational& rhs);
    friend bool operator<=(const Rational& lhs, const Rational& rhs);
    friend bool operator>=(const Rational& lhs, const Rational& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);
};

// Rational op Rational
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

// int op Rational
Rational operator+(int lhs, const Rational& rhs);
Rational operator-(int lhs, const Rational& rhs);
Rational operator*(int lhs, const Rational& rhs);
Rational operator/(int lhs, const Rational& rhs);

// Rational op int
Rational operator+(const Rational& lhs, int rhs);
Rational operator-(const Rational& lhs, int rhs);
Rational operator*(const Rational& lhs, int rhs);
Rational operator/(const Rational& lhs, int rhs);