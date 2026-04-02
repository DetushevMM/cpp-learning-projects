#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>

class Complex {
private:
    double re_;
    double im_;

    static constexpr double EPS = 1e-12;

public:
    Complex() : re_(0.0), im_(0.0) {}
    explicit Complex(double re) : re_(re), im_(0.0) {}
    Complex(double re, double im) : re_(re), im_(im) {}

    double Real() const { return re_; }
    double Imag() const { return im_; }

    void SetReal(double re) { re_ = re; }
    void SetImag(double im) { im_ = im; }

    double Abs() const {
        return std::hypot(re_, im_);
    }

    // операции присваивания с арифметикой, Complex справа
    Complex& operator+=(const Complex& rhs) {
        re_ += rhs.re_;
        im_ += rhs.im_;
        return *this;
    }

    Complex& operator-=(const Complex& rhs) {
        re_ -= rhs.re_;
        im_ -= rhs.im_;
        return *this;
    }

    Complex& operator*=(const Complex& rhs) {
        double r = re_ * rhs.re_ - im_ * rhs.im_;
        double i = re_ * rhs.im_ + im_ * rhs.re_;
        re_ = r;
        im_ = i;
        return *this;
    }

    Complex& operator/=(const Complex& rhs) {
        double d = rhs.re_ * rhs.re_ + rhs.im_ * rhs.im_;
        if (std::abs(d) < EPS) {
            throw std::invalid_argument("Division by zero");
        }

        double r = (re_ * rhs.re_ + im_ * rhs.im_) / d;
        double i = (im_ * rhs.re_ - re_ * rhs.im_) / d;
        re_ = r;
        im_ = i;
        return *this;
    }

    // операции присваивания с арифметикой с double справа
    Complex& operator+=(double rhs) {
        re_ += rhs;
        return *this;
    }

    Complex& operator-=(double rhs) {
        re_ -= rhs;
        return *this;
    }

    Complex& operator*=(double rhs) {
        re_ *= rhs;
        im_ *= rhs;
        return *this;
    }

    Complex& operator/=(double rhs) {
        if (std::abs(rhs) < EPS) {
            throw std::invalid_argument("Division by zero");
        }
        re_ /= rhs;
        im_ /= rhs;
        return *this;
    }

    // унарные операции
    Complex operator+() const { return *this; }
    Complex operator-() const { return Complex(-re_, -im_); }

    // бинарные операции Complex
    friend Complex operator+(Complex lhs, const Complex& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Complex operator-(Complex lhs, const Complex& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Complex operator*(Complex lhs, const Complex& rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Complex operator/(Complex lhs, const Complex& rhs) {
        lhs /= rhs;
        return lhs;
    }

    // бинарные операции с double
    friend Complex operator+(Complex lhs, double rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Complex operator-(Complex lhs, double rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Complex operator*(Complex lhs, double rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Complex operator/(Complex lhs, double rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend Complex operator+(double lhs, Complex rhs) {
        rhs += lhs;
        return rhs;
    }

    friend Complex operator-(double lhs, Complex rhs) {
        rhs.re_ = lhs - rhs.re_;
        rhs.im_ = -rhs.im_;
        return rhs;
    }

    friend Complex operator*(double lhs, Complex rhs) {
        rhs *= lhs;
        return rhs;
    }

    friend Complex operator/(double lhs, Complex rhs) {
        double d = rhs.re_ * rhs.re_ + rhs.im_ * rhs.im_;
        if (std::abs(d) < EPS) {
            throw std::invalid_argument("Division by zero");
        }
        double r = lhs * rhs.re_ / d;
        double i = -lhs * rhs.im_ / d;
        return Complex(r, i);
    }

    // сравнение == и !=
    friend bool operator==(const Complex& a, const Complex& b) {
        return std::abs(a.re_ - b.re_) < EPS &&
            std::abs(a.im_ - b.im_) < EPS;
    }

    friend bool operator!=(const Complex& a, const Complex& b) {
        return !(a == b);
    }
};