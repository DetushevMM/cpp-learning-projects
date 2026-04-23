/*
Вагоны
Вы — машинист. Вам поручено реализовать функцию void MakeTrain(), чтобы сформировать поезд из набора вагонов.

У каждого вагона есть номер (помещается в int). Номера вагонов внутри состава могут повторяться. 
Изначально путь, на котором формируется состав, пустой. 
Вы должны уметь выполнять следующие команды, которые поступают в отдельных строках на входе:
- +left W — добавить вагон с номером W слева
- +right W — добавить вагон с номером W справа
- -left N — отцепить и убрать N вагонов слева
- -right N — отцепить и убрать N вагонов справа
В последних двух командах N может быть больше текущей длины состава — в этом случае надо убрать весь состав целиком. 
Отцеплять вагоны по одному может быть долго: постарайтесь сразу отцеплять по N штук. 

Напечатайте через пробел номера вагонов получившегося состава, если смотреть на них слева направо. 
В самом конце напечатайте перевод строки.

На вход подаются строки с командами в указанном формате. Всего будет не более 1 млн команд. 
Оформите ваше решение в функции void MakeTrain(). 
Эта функция должна читать данные со стандартного потока ввода и печатать их в стандартный поток вывода. 
Подключите все необходимые библиотеки. В вашем решении не должно быть функции main.

Пример
Ввод                     Вывод

+left 1                   3 1
+right 2
+left 3
-right 1
*/


#include <iostream>
#include <deque>
#include <string>

void MakeTrain() {
    std::deque<int> train;
    std::string command;

    while (std::getline(std::cin, command)) {
        if (command.empty()) {
            continue;
        }

        int W = 0;
        int N = 0;

        if (command[0] == '+') {
            size_t pos = command.find(' ');
            std::string direction = command.substr(1, pos - 1);
            W = std::stoi(command.substr(pos + 1));

            if (direction == "left") {
                train.push_front(W);
            } else {
                train.push_back(W);
            }
        } else if (command[0] == '-') {
            size_t pos = command.find(' ');
            std::string side_str = command.substr(1, pos - 1);
            N = std::stoi(command.substr(pos + 1));

            if (side_str == "left") {
                if (N >= (int)train.size()) {
                    train.clear();
                } else {
                    train.erase(train.begin(), train.begin() + N);
                }
            } else {
                if (N >= (int)train.size()) {
                    train.clear();
                } else {
                    auto end_it = train.end();
                    auto start_it = end_it - N;
                    train.erase(start_it, end_it);
                }
            }
        }
    }
    for (size_t i = 0; i < train.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << train[i];
    }
    std::cout << "\n";
}