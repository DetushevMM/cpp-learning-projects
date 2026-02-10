#pragma once

/*Реализуйте шаблонную функцию IsSortedUntil, которая принимает два указателя: указатель на начало и конец последовательности. 
Функция ищет первый элемент с начала, который нарушает отсортированность последовательности по неубыванию, и возвращает указатель на него. 
Если последовательность отсортирована, то возвращается указатель на конец последовательности. Из сравнений можно использовать только операцию "меньше" (<).*/

template <typename T>
const T* IsSortedUntil(const T* begin, const T* end) {
    if (begin == end) {
        return end;
    }

    auto current = begin;
    current++;

    while (current != end) {
        if (*current < *(current - 1)) {
            return current;
        }
        current++;
    }
    return end;
}