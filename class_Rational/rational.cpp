#include "rational.hpp"
#include <cstdlib>

// Исключение
const char* RationalDivisionByZero::what() const noexcept {
    return "Division by zero";
}

// Вспомогательные методы Rational
int Rational::GCD(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);

    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void Rational::Normalize() {
    if (denominator_ == 0) {
        throw RationalDivisionByZero{};
    }

    if (denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    }

    if (numerator_ == 0) {
        denominator_ = 1;
        return;
    }

    int g = GCD(numerator_, denominator_);
    numerator_ /= g;
    denominator_ /= g;
}

// Конструкторы
Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int numerator) : numerator_(numerator), denominator_(1) {
}

Rational::Rational(int numerator, int denominator)
    : numerator_(numerator), denominator_(denominator) {
    Normalize();
}

// Getters
int Rational::GetNumerator() const {
    return numerator_;
}

int Rational::GetDenominator() const {
    return denominator_;
}

// Setters
void Rational::SetNumerator(int numerator) {
    numerator_ = numerator;
    Normalize();
}

void Rational::SetDenominator(int denominator) {  // NOLINT
    if (denominator == 0) {
        throw RationalDivisionByZero{};
    }
    denominator_ = denominator;
    Normalize();
}

// Операторы присваивания с арифметикой
Rational& Rational::operator+=(const Rational& rhs) {
    numerator_ = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
    denominator_ *= rhs.denominator_;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    numerator_ = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
    denominator_ *= rhs.denominator_;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator_ *= rhs.numerator_;
    denominator_ *= rhs.denominator_;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.numerator_ == 0) {
        throw RationalDivisionByZero{};
    }

    numerator_ *= rhs.denominator_;
    denominator_ *= rhs.numerator_;
    Normalize();
    return *this;
}

// Унарные операторы + и -
Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    return { -numerator_, denominator_ };
}

// Инкременты
Rational& Rational::operator++() {
    *this += Rational(1);
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    ++(*this);
    return temp;
}

// Декременты
Rational& Rational::operator--() {
    *this -= Rational(1);
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp = *this;
    --(*this);
    return temp;
}

// Операторы сравнения ==, !=, <, <=, >, >=
bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator_ == rhs.numerator_ &&
        lhs.denominator_ == rhs.denominator_;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator_ * rhs.denominator_ <
        rhs.numerator_ * lhs.denominator_;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

// Бинарные операторы класс Rational +,-,*,/ класс Rational
Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res += rhs;
    return res;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res -= rhs;
    return res;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res *= rhs;
    return res;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res /= rhs;
    return res;
}

// Бинарные операторы int +,-,*,/ класс Rational
Rational operator+(int lhs, const Rational& rhs) {
    Rational res(lhs);
    res += rhs;
    return res;
}

Rational operator-(int lhs, const Rational& rhs) {
    Rational res(lhs);
    res -= rhs;
    return res;
}

Rational operator*(int lhs, const Rational& rhs) {
    Rational res(lhs);
    res *= rhs;
    return res;
}

Rational operator/(int lhs, const Rational& rhs) {
    Rational res(lhs);
    res /= rhs;
    return res;
}

// Бинарные операторы класс Rational +,-,*,/ int
Rational operator+(const Rational& lhs, int rhs) {
    Rational res = lhs;
    res += Rational(rhs);
    return res;
}

Rational operator-(const Rational& lhs, int rhs) {
    Rational res = lhs;
    res -= Rational(rhs);
    return res;
}

Rational operator*(const Rational& lhs, int rhs) {
    Rational res = lhs;
    res *= Rational(rhs);
    return res;
}

Rational operator/(const Rational& lhs, int rhs) {
    Rational res = lhs;
    res /= Rational(rhs);
    return res;
}

// Потоковый вывод
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1) {
        os << r.numerator_;
    }
    else {
        os << r.numerator_ << '/' << r.denominator_;
    }
    return os;
}

// Потоковый ввод
std::istream& operator>>(std::istream& is, Rational& r) {
    int num = 0;
    int den = 1;
    char c = 0;

    if (is >> num) {
        if (is.peek() == '/') {
            is >> c >> den;
        }
    }

    r = Rational(num, den);
    return is;
}