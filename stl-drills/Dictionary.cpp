/*
Словарь
Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к парному ему слову. 
Все слова в словаре различны. Для каждого данного слова определите его синоним.

Для решения данной задачи используйте std::unordered_map

Формат ввода
- Программа получает на вход количество пар синонимов N(0≤N≤10^5). 
- Далее следует N строк, каждая строка содержит ровно два слова-синонима.
- Затем идет число Q(1≤Q≤10^5) — количество запросов к словарю. 
- Далее на каждой следующей из Q строк идет слово, к которому надо вывести синоним.

Формат вывода
Программа должна вывести синонимы к данным слову на отдельных строках.

Пример
Ввод                       Вывод
3                          car
car plane                  base
mouse cat                  stream
base stream
3
plane
stream
base

Примечания: Подумайте, почему бы не использовать std::map. Используйте быстрый ввод.
*/

#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::unordered_map<std::string, std::string> dict_synonyms;
  dict_synonyms.reserve(n * 2);

  for (int i = 0; i < n; ++i) {
    std::string word1;
    std::string word2;

    std::cin >> word1 >> word2;

    // Добавялем двусторонние связи
    dict_synonyms[word1] = word2;
    dict_synonyms[word2] = word1;
  }
  int q = 0;
  std::cin >> q;

  // Обработаем запросы
  for (int i = 0; i < q; ++i) {
    std::string query;
    std::cin >> query;

    std::cout << dict_synonyms[query] << '\n';
  }
  return 0;
}