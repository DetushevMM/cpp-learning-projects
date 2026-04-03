#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>

class Complex {
private:
    double re_;
    double im_;
    // Константа для сравнения вещественных чисел
    static constexpr double EPS = 1e-12;

public:
    // Конструкторы
    Complex() : re_(0.0), im_(0.0) {}
    // Убрал explicit, чтобы можно было складывать Complex c = c + 5.0; 
    // В математических классах это считается хорошим тоном.
    Complex(double re) : re_(re), im_(0.0) {}
    Complex(double re, double im) : re_(re), im_(im) {}

    // Геттеры и сеттеры
    double Real() const { return re_; }
    double Imag() const { return im_; }
    void SetReal(double re) { re_ = re; }
    void SetImag(double im) { im_ = im; }

    // Модуль комплексного числа
    double Abs() const {
        return std::hypot(re_, im_);
    }

    // --- Операторы инкремента ---

    // Префиксный (++c)
    Complex& operator++() {
        re_ += 1.0;
        return *this;
    }

    // Постфиксный (c++)
    Complex operator++(int) {
        Complex temp = *this;
        re_ += 1.0;
        return temp;
    }
    // Префиксный декремент (--c)
    // Сначала уменьшает значение, потом возвращает ссылку на объект
    Complex& operator--() {
        re_ -= 1.0;
        return *this;
    }

    // Постфиксный декремент (c--)
    // Сначала сохраняет копию старого значения, уменьшает текущее, 
    // а возвращает сохраненную копию (состояние "до изменения")
    Complex operator--(int) {
        Complex temp = *this;
        re_ -= 1.0;
        return temp;
    }


    // --- Операторы присваивания с арифметикой ---

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
        double new_re = re_ * rhs.re_ - im_ * rhs.im_;
        double new_im = re_ * rhs.im_ + im_ * rhs.re_;
        re_ = new_re;
        im_ = new_im;
        return *this;
    }

    Complex& operator/=(const Complex& rhs) {
        double d = rhs.re_ * rhs.re_ + rhs.im_ * rhs.im_;
        if (std::abs(d) < EPS) {
            throw std::invalid_argument("Division by zero");
        }
        double new_re = (re_ * rhs.re_ + im_ * rhs.im_) / d;
        double new_im = (im_ * rhs.re_ - re_ * rhs.im_) / d;
        re_ = new_re;
        im_ = new_im;
        return *this;
    }

    // --- Бинарные операции ---
    // Используем friend, чтобы можно было писать и (c1 + c2), и (c1 + 5.0), и (5.0 + c1)
    friend Complex operator+(Complex lhs, const Complex& rhs) {
        return lhs += rhs;
    }

    friend Complex operator-(Complex lhs, const Complex& rhs) {
        return lhs -= rhs;
    }

    friend Complex operator*(Complex lhs, const Complex& rhs) {
        return lhs *= rhs;
    }

    friend Complex operator/(Complex lhs, const Complex& rhs) {
        return lhs /= rhs;
    }

    // --- Сравнение ---
    friend bool operator==(const Complex& a, const Complex& b) {
        return std::abs(a.re_ - b.re_) < Complex::EPS &&
               std::abs(a.im_ - b.im_) < Complex::EPS;
    }

    friend bool operator!=(const Complex& a, const Complex& b) {
        return !(a == b);
    }

    // --- Ввод и вывод ---

    // Красивый вывод: "a + bi" или "a - bi"
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.re_;
        if (c.im_ > 0) {
            os << " + " << c.im_ << "i";
        } else if (c.im_ < 0) {
            os << " - " << std::abs(c.im_) << "i";
        }
        // Если im == 0, выводится только действительная часть
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        is >> c.re_ >> c.im_;
        return is;
    }
};
