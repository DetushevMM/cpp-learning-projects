#include "cstring.hpp"

//1. Вычисляет длину строки str (без учета нулевого символа).
size_t Strlen(const char* str) {
    size_t count = 0;
    while (str[count] != '\0') {
        count += 1;
    }
    return count;
}

//2. Лексографическое сравнение двух строк
int Strcmp(const char* first, const char* second) {
    while (*first != '\0' && *second != '\0') {
        if (*first < *second) {
            return -1;
        } 
        if (*first > *second) {
            return 1;
        }
        ++first;
        ++second;
    }  
    // Проверяем оставшиеся символы
    if (*first == '\0' && *second == '\0') {
        return 0;
    } 
    if (*first == '\0') {
        return -1;  // first короче second
    } 
    return 1;   // first длиннее second
}

//3. Лексикографическое сравнение первых count символов строк (либо пока не встретит нулевой символ).
int Strncmp(const char* first, const char* second, size_t count) {
    size_t i = 0;

    // Пока не достигли count и символы совпадают
    while (i < count && *first == *second && *first != '\0') {
        ++first;
        ++second;
        ++i;
    }

    // Если сравнили ровно count символов — строки равны
    if (i == count) {
        return 0;
    } 
    if (*first < *second) {  // Иначе возвращаем знак разницы текущих символов
        return -1;
    }
    if (*first > *second) {
        return 1;
    }
    return 0;
}

//4. Возвращает указатель на первое появление символа symbol в строке str
const char* Strchr(const char* str, char symbol) {
    while (*str != '\0') {
        if (*str == symbol) {
            return str;
        } 
        ++str;
    }
    if (symbol == '\0') {
        return str;
    }
    return nullptr;
}

//5. Возвращает указатель на последнее появление символа symbol в строке str (с учетом нулевого символа), либо нулевой указатель, если такого символа нет.
const char* Strrchr(const char* str, char symbol) {
    const char* last = nullptr;
    while (*str != '\0') {
        if (*str == symbol) {
            last = str;
        }
        ++str;
    }
    if (symbol == '\0') {
        last = str;
    }
    
    return last;
}

//6.  Возвращает количество первых символов dest, которые встречаются в строке src (без учета нулевого символа).
size_t Strspn(const char* dest, const char* src) {
    size_t count = 0;

    for (; *dest != '\0'; dest++) {
        auto s = src;
        while (*s != '\0' && *s != *dest) {
            ++s;
        }
        if (*s == '\0') {  // символ не найден в src
            break;          // останавливаем внешний цикл
        }
        count++;
    }

    return count;
}

//7. Возвращает количество первых символов dest, которые не встречаются в строке src (без учета нулевого символа).
size_t Strcspn(const char* dest, const char* src) {
    size_t count = 0;
     for (; *dest != '\0'; dest++) {
        auto s = src;
        for (;*s != '\0'; ++s) {
            if (*dest == *s) {
                return count;
            }
        }
        count += 1;
     }
     return count;
}

//8. Возвращает указатель на первый элемент dest, который лежит в breakset, либо нулевой указатель, если такого элемента нет.
const char* Strpbrk(const char* dest, const char* breakset) {
    for (; *dest != '\0'; ++dest) {
        for (auto b = breakset; *b != '\0'; ++b) {
            if (*dest == *b) {
                return dest;
            } 
        } 
    } 
    return nullptr;
}

//9. Осуществляет поиск подстроки pattern в строке str. Возвращает указатель на начало первого вхождения, либо нулевой указатель, если вхождения найдено не было.
const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return str;
    }
    if (*str == '\0') {
        return nullptr;
    }

    auto s = str;
    for (; *s != '\0'; s++) {
        auto current = s;
        auto p = pattern; 
        while (*p != '\0' && *current == *p) {
            ++current;
            ++p;
        }
        if (*p == '\0') {
            return s;
        }
    }
    return nullptr;
}

//10. Принимает строку src и копирует ее содержимое (вместе с нуль-терминатором) в dest.
char* Strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

//11. Принимает строку src n копирует ровно count символов из src. Если count больше размера src, то оставшиеся символы заполняются нуль-символами. Возвращает dest.
char* Strncpy(char* dest, const char* src, size_t count) {
    size_t i = 0;
    auto d = dest;
    auto s = src;
    while (i < count && *s != '\0') {
        *d = *s;
        ++d;
        ++s;
        i++; 
    }
    while (i < count) {
        *d = '\0';
        ++d;
        i++;
    }
    return dest;
}

//12. Приписывает строку src в конец строки dest (конкатенация строк).
char* Strcat(char* dest, const char* src) {
    auto d = dest;
    //Ищем конец строки и ставим указатель на место '\0'
    while (*d != '\0') {
        d++;
    }
    //Копируем строку src в конец dest
    while (*src != '\0') {
        *d = *src;
        d++;
        src++;
    }
    *d = '\0'; // добавляем в конец ноль.
    return dest;
}

// 13. Приписывает строку src в конец строки dest, но добавляет только первые count символов из src + нулевой символ.
// Если count больше чем длина src, то работает так же как и Strcat(dest, src). Возвращает dest.
char* Strncat(char* dest, const char* src, size_t count) {
    auto d = dest;
    while (*d != '\0') {
        d++;
    }
    size_t i = 0;
    while (*src != '\0' && i < count) {
        *d = *src;
        src++;
        d++;
        i++;
    }
    *d = '\0';
    return dest;
}