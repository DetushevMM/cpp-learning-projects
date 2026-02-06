#pragma once

/*Пришлите заголовочный файл с определениями трех шаблонных функций для работы с отсортированными последовательностями. Каждая функция принимает три аргумента: 
begin - указатель на начало последовательности, 
end - указатель на конец последовательности (элемент следующий за последним), 
value - запрос.

Важно: используйте только сравнение на меньше (<) и избегайте лишних копирований элементов. 
То есть считайте, что элементы последовательности не копируемы и могут быть сравнены только с помощью операции <.*/

// LowerBound - функция, осуществляющая поиск первого элемента не меньшего (≥) value на полуинтервале [begin,end). 
// Возвращает указатель на найденный элемент, либо end, если такого нет.

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
    while (begin < end) {
        const T* mid = begin + (end - begin) / 2;
        if (*mid < value) {
            begin = mid + 1;
        } else {
            end = mid;
        } 
    }
    return begin;
}

// UpperBound - функция, осуществляющая поиск первого элемента строго большего (>) value на полуинтервале [begin,end). 
// Возвращает указатель на найденный элемент, либо end, если такого нет.

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
    while (begin < end) {
        const T* mid = begin + (end - begin) / 2;
        if (!(value < *mid)) {
            begin = mid + 1;
        } else {
            end = mid;
        } 
    }
    return begin;
}

// BinarySearch - функция, осуществляющая проверку наличия элемента value в отсортированной последовательности [begin,end). 
// Возвращает true, если и только если на полуинтервале [begin,end) имеется значение value.

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
    while (begin < end) {
        const T* mid = begin + (end - begin) / 2;
        if (*mid < value) {
            begin = mid + 1;
        } else if (value < *mid) {
            end = mid;
        } else {
            return true;
        }
    }
    return false;
}