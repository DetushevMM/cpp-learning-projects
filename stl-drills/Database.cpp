/*
База данных
Дана база данных о продажах некоторого интернет-магазина. 
Каждая строка входного файла представляет собой запись вида покупатель-товар-количество, где 
- покупатель — имя покупателя (строка без пробелов), 
- товар — название товара (строка без пробелов), 
- количество — количество приобретённых единиц товара.

Создайте список всех покупателей и для каждого покупателя подсчитайте количество приобретенных им единиц каждого вида товаров.

Формат ввода
- Во входном файле записано не более 10^5 строк в указанном формате.
- Имена покупателей и названия товаров представляют собой строки из заглавных и строчных латинских букв не длиннее 10 символов. 
- Количество товара в каждой покупке — натуральное число, не превышающее 10^6.

Формат вывода
Выведите список всех покупателей в лексикографическом порядке, после имени каждого покупателя выведите двоеточие.
Затем выведите список названий всех приобретенных данным покупателем товаров в лексикографическом порядке.
После названия каждого товара выведите количество единиц товара, приобретенных данным покупателем.

Информация о каждом товаре выводится в отдельной строке.

Пример
Ввод                                     Вывод
Ivanov paper 10                          Ivanov:
Petrov pen 5                             envelope 5
Ivanov marker 3                          marker 3
Ivanov paper 7                           paper 17
Petrov envelope 20                       Petrov:
Ivanov envelope 5                        envelope 20
                                         pen 5
*/

#include <iostream>
#include <map>
#include <string>

class ShopDataBase {
  // внешний map сортирует покупаелей, а внутренний - товары (buyer->(product->count))
  std::map<std::string, std::map<std::string, size_t>> database_;

 public:
  void AddPurchase(const std::string& client, const std::string& item, size_t count) {
    database_[client][item] += count;
  }

  void Print() const {
    for (const auto& [client, items] : database_) {
      std::cout << client << ":\n";
      for (const auto& [item, count] : items) {
        std::cout << item << ' ' << count << '\n';
      }
    }
  }
};

int main() {
  ShopDataBase db;
  std::string client;
  std::string item;
  size_t count = 0;
  while (std::cin >> client >> item >> count) {
    db.AddPurchase(client, item, count);
  }
  db.Print();
  return 0;
}
