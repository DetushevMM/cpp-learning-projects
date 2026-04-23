/*
Файловая система
Дан список всех файлов в некоторой файловой системе. Необходимо вывести все непустые директории этой файловой системы в лексикографическом порядке.

Гарантируется, что все пути начинаются от корня файловой системы. Все пути состоят из слешей (/), латинских символов, цифр и точек. Два слеша никогда не стоят подряд.

Формат ввода
На вход подаются строки, описывающие пути ко всем файлам в системе. 
Каждый путь содержится в отдельной строке. Число строк не превосходит 10000.

Формат вывода
Выведите все непустые директории в этой файловой системе в лексикографическом порядке. 
Каждый путь должен начинаться со слеша и заканчиваться слешом.

Пример 1                                    Пример 2
Ввод                                        Ввод

/docs/README.txt                            /home/guest/homework/A/main.cpp
/docs/LICENSE.txt                           /root/test.cpp
/boot/grub                                  /root/tests/01
/init                                       /root/tests/01.a
                                            /bin/bash
                                            /usr/bin/perl

Вывод                                        Вывод

/                                            /
/boot/                                       /bin/
/docs/                                       /home/
                                             /home/guest/
                                             /home/guest/homework/
                                             /home/guest/homework/A/
                                             /root/
                                             /root/tests/
                                             /usr/
                                             /usr/bin/
*/


#include <iostream>
#include <string>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<std::string> dirs;
    std::string path;

    while (std::getline(std::cin, path)) {
        if (!path.empty() && path.back() == '\r') {
            path.pop_back();
        }
        if (path.empty()) continue;

        dirs.insert("/");

        for (size_t i = 1; i < path.size(); ++i) {
            if (path[i] == '/') {
                dirs.insert(path.substr(0, i + 1));
            }
        }
    }

    for (const auto& d : dirs) {
        std::cout << d << '\n';
    }

    return 0;
}