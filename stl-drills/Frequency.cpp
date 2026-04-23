/*
Частотность
Дан текст. Выведите все слова, встречающиеся в тексте, по одному на каждую строку. 
Слова должны быть отсортированы по убыванию их количества появления в тексте, а при одинаковой частоте появления в лексикографическом порядке.

Формат ввода
Вводится текст - последовательность строк через пробел или перенос строки.

Формат вывода
Выведите ответ на задачу.

Пример
Ввод                                  Вывод
hi                                    damme
hi                                    is
what is your name                     name
my name is bond                       van
james bond                            bond
my name is damme                      claude
van damme                             hi
claude van damme                      my
jean claude van damme                 james
                                      jean
                                      what
                                      your
Примечания: Указание. 
После того, как вы создадите словарь всех слов, вам захочется отсортировать его по частоте встречаемости слова. 
Желаемого можно добиться, если создать список, элементами которого будут пары из двух элементов: частота встречаемости слова и само слово. 
Например, [(2,hi),(1,what),(3,is)]. 
Тогда стандартная сортировка будет сортировать список пар, при этом кортежи сравниваются по первому элементу, а если они равны, то по второму. 
Это почти то, что требуется в задаче.
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

bool Compare(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
  if (a.second != b.second) {
    // По убыванию частоты
    return a.second > b.second;
  }
  // По возрастанию лексикографически
  return a.first < b.first;
}

int main() {
  std::map<std::string, int> wordcount;
  std::string word;

  while (std::cin >> word) {
    wordcount[word]++;
  }

  // Перенос в вектор
  std::vector<std::pair<std::string, int>> words(wordcount.begin(), wordcount.end());

  // Сортировка с компаратором
  std::sort(words.begin(), words.end(), Compare);

  for (size_t i = 0; i < words.size(); ++i) {
    std::cout << words[i].first << '\n';
  }
  return 0;
}