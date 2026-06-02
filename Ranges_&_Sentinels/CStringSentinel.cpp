/*
CStringSentinel
Стандартные алгоритмы C++ требуют пары итераторов (begin, end) для определения диапазона, над которым они будут работать. 
При работе с C-style строками, это означает, что предварительно нужно вычислить длину строки, чтобы получить итератор конца. 
Это может быть неэффективно, особенно для длинных строк.

Концепция итератор-сентинел (iterator-sentinel) позволяет использовать специальный объект-"признак конца диапазона", который при сравнении с итератором указывает нужно ли продолжать итерацию. 
Таким образом, появляется возможность обрабатывать C-style строки библиотекой <algorithms> за один проход, без необходимости вычислять длину строки заранее.

Реализуйте класс CStringSentinel, который будет служить итератором-сентинелем для C-style строк и заканчивать итерацию по достижении нулевого символа ('\0').

С помощью этого класса и алгоритма std::ranges::all_of проверьте, что все символы в строке являются буквами (std::isalpha).

Формат ввода
Строка, состоящая из не более чем 10^6 символов.

Формат вывода
YES, если все символы в строке являются буквами, и NO в противном случае.
*/

#include <iostream>
#include <ranges>
#include <string>
#include <algorithm>

struct CStringSentinel {
 public:
  friend bool operator==(const char* ptr, CStringSentinel) {
    return *ptr == '\0';
  }

  friend bool operator==(CStringSentinel, const char* ptr) {
    return *ptr == '\0';
  }
};

bool IsLetter(char c) {
  return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

int main() {
  std::string str;
  std::cin >> str;

  bool ok = std::ranges::all_of(str.c_str(), CStringSentinel{}, IsLetter);

  if (ok) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}