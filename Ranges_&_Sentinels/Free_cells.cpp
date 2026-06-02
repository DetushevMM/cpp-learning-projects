/*
Свободные клетки
Дана строка, состоящая из символов '.' и '#'. Символ '.' означает свободную клетку, символ '#' — занятую клетку.

Дано число k. Нужно вывести все позиции i, такие что отрезок длины k, начинающийся в позиции i, полностью свободен (то есть состоит из символов '.').

Используйте views::iota и views::filter для решения задачи.

Формат ввода
В первой строке задана строка, состоящая из символов '.' и '#'. 
Длина строки n не превышает 10^7 символов. Во второй строке задано целое число k (1≤k≤n).

Формат вывода
Выведите в одной строке через пробел все позиции i, такие что отрезок длины k, начинающийся в позиции i, полностью свободен. 
Если таких позиций нет, выведите пустую строку. Индексация начинается с нуля.

Пример
Ввод                 Вывод
..#..                0 3
2
*/

#include <iostream>
#include <string>
#include <ranges>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  int k = 0;
  std::cin >> k;

  const int n = static_cast<int>(s.size());

  if (k > n) {
    std::cout << '\n';
    return 0;
  }

  const int m = n - k + 1;

  int blocked = 0;
  for (int i = 0; i < k; ++i) {
    blocked += (s[i] == '#');
  }

  auto positions = std::views::iota(0, m) | std::views::filter([&](int i) {
                     const bool ok = (blocked == 0);
                     // готовим окно для следующей позиции i + 1
                     if (i + 1 < m) {
                       blocked -= (s[i] == '#');
                       blocked += (s[i + k] == '#');
                     }
                     return ok;
                   });

  bool first = true;
  for (int pos : positions) {
    if (!first) {
      std::cout << ' ';
    }
    std::cout << pos;
    first = false;
  }
  std::cout << '\n';
  return 0;
}
