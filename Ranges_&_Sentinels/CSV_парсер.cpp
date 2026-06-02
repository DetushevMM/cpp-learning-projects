/*
CSV парсер
CSV (Comma-Separated Values) — это текстовый формат для представления табличных данных, в котором каждая строка соответствует одной записи, а поля внутри строки разделены запятыми. 
Например: Anna,Smith,30,,8.7 — строка таблицы с пятью полями, в которой четвертое поле пустое.

Реализуйте программу, которая принимает на вход строку в формате CSV, и вычисляет сумму всех числовых полей.

Строка может содержать только целые числа, строки и пустые поля.

Используйте views::filter и views::split.

Формат ввода
Одна строка в формате CSV. Количество полей в строке не превышает 10^6. 
Значения числовых полей — целые числа, не превышающие 100 по модулю.

Формат вывода
Одно число — сумма всех числовых полей в строке.

Пример
Ввод                                            Вывод
6,,Anna,-25,Ivanova                             -19
*/

#include <iostream>
#include <string>
#include <ranges>

bool IsNumber(const std::string& s) {
  if (s.empty()) {
    return false;
  }

  int start = 0;

  if (s[0] == '-') {
    if (s.size() == 1) {
      return false;
    }
    start = 1;
  }

  for (size_t i = start; i < s.size(); ++i) {
    if (!isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string s;
  std::cin >> s;

  int sum = 0;

  auto fields = s | std::views::split(',');

  auto filter_num = [](auto part) { std::string str(part.begin(), part.end()); return IsNumber(str); };

  auto numbers = (fields | std::views::filter(filter_num));

  for (auto field : numbers) {
    std::string str(field.begin(), field.end());

    sum += std::stoi(str);
  }
  std::cout << sum << '\n';
}
