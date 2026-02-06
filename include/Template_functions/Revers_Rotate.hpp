#pragma once

/*Реализуйте шаблонную функцию Reverse, которая принимает указатель на начало и указатель на конец последовательности и разворачивает ее.
Новая последовательность записывается поверх старой*/

template <class T>
void Reverse(T* begin, T* end) {
    if (end - begin <= 1) {
        return;
    }

    auto left = begin;
    auto right = end - 1;

    while (left < right) {
        auto tmp = *left;
        *left = *right;
        *right = tmp;

        ++left;
        --right;
    }
}

/*Также реализуйте функцию Rotate, которая принимает указатели: 
- begin - начало последовательности, 
- mid - указатель на некоторый элемент той же последовательности, 
- end - конец последовательности и меняет местами подпоследовательности [begin, mid) и [mid, end) (осуществляет циклический сдвиг).*/
template <class T>
void Rotate(T* begin, T* mid, T* end) {
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}