#pragma once

template <typename T>
T* Unique(T* begin, T* end) {
    //  Техника двух указателей
    if (begin == end) {
        return end;
    }
    if (end - begin == 1) {
        return begin + 1;
    }
    //указатель показывает куда перемещается следующий уникальный элемент
    T* write = begin;
    //указатель перебирает всю последовательность
    T* read = begin + 1;  // начинаем перебор с 3 элемента

    while (read < end) {
        if (*write < *read || *read < *write) {
            ++write;
            if (write != read) {
                *write = *read;
            } 
        }
        ++read;
    }
    return write + 1;
}