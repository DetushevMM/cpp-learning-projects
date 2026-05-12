/*
Bank
У банка есть клиенты. Каждый клиент имеет ровно один счет.

Напишите программу, которая будет выполнять последовательность запросов таких двух видов:
- Начинается с числа 1, затем через пробел следует имя клиента (слово из латинских букв), 
  далее через пробел идет сумма денег, которую клиент кладет или берет из счета в банке (целое число, не превышает по модулю 10000).
- Начинается с числа 2, через пробел следует имя клиента. 
  На каждый такой запрос программа должна ответить какая сумма в данный момент есть на счету заданного клиента. 
  Если такое имя клиента пока ни разу не упоминалось в запросах вида 1, выводите вместо числа слово «ERROR».

В начале работы программы у всех клиентов на счету 0. Затем суммы могут становиться как положительными, так и отрицательными.

Обратите внимание, что в ситуации, когда клиент снял суммарно ровно столько же денег, сколько положил, сумма на счете становится равной 0, но, раз его имя уже встречалось, нулевое значение не является основанием выводить «ERROR».

Для решения задачи используйте ассоциативный контейнер.

Формат ввода
1. Первая строка стандартного входного потока количество запросов N(1≤N≤10^5). 
2. Далее следуют N строк в каждой из которых описан один из двух описанных выше видов запроса.

Формат вывода
На каждый запрос 2-го вида нужно вывести текущее значение на счету заданного клиента (или слово «ERROR»).

Пример
Ввод                           Вывод
7                              3
1 asdf 3                       1
1 zxcv 5                       ERROR
2 asdf                         5
1 asdf -2
2 asdf
2 lalala
2 zxcv
*/

#include <iostream>
#include <unordered_map>
#include <string>

class BankAccounts {
  std::unordered_map<std::string, int> accounts_;

 public:
  void ChangeAmmount(const std::string& accaunt_name, int amount) {
    accounts_[accaunt_name] += amount;
  }

  [[nodiscard]] std::pair<bool, int> GetMoney(const std::string& accaunt_name) const {
    if (auto item = accounts_.find(accaunt_name); item != accounts_.end()) {
      return {true, item->second};
    }
    return {false, 0};
  }
};

const int kChangeType = 1;
// const int kGetType = 2;

int main() {
  size_t n = 0;
  std::cin >> n;
  BankAccounts bank;
  
  for (size_t i = 0; i < n; ++i) {
    int type = 0;
    std::string account;
    std::cin >> type >> account;

    if (type == kChangeType) {
      int value = 0;
      std::cin >> value;
      bank.ChangeAmmount(account, value);
    } else {  // const int kGetType = 2;
      const auto res = bank.GetMoney(account);
      if (res.first) {
        std::cout << res.second << '\n';
      } else {
        std::cout << "ERROR\n";
      }
    }
  }
  return 0;
}
