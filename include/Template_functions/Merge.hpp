#pragma once

/*Реализуйте шаблонную функцию Merge (Слияние)**, которая принимает две отсортированные последовательности и сливает их одну большую отсортированную.
Функция должна принимать 5 аргументов: 
- first_begin, first_end - указатели на начало и конец первой последовательности; 
- second_begin, second_end - начало и конец второй последовательности; 
- out - указатель на начало итоговой последовательности (куда записывать ответ).

Последовательности first, second и out могут хранить значения разных типов!*/

template <class T, class U, class W>
W* Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, W* out) {
    auto first = first_begin;
    auto second = second_begin;
    auto current_out = out;

    while (first < first_end && second < second_end) {
        if (*first < *second) {
            *current_out = *first;
            ++first;
        } else {
            *current_out = *second;
            ++second;
        }
        ++current_out;
    }
// Если в первой последовательности остались элементы, копируем их
    while (first < first_end) {
        *current_out = *first;
        ++first;
        ++current_out;
    }
// Если во второй последовательности остались элементы, копируем их
    while (second < second_end) {
        *current_out = *second;
        ++second;
        ++current_out;
    }

    return current_out;
}