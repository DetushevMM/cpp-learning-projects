#pragma once

#include <cstddef>
#include <iostream>

class String {
private:
    char* data_;       // указатель на буфер
    size_t size_;      // текущий размер
    size_t capacity_;  // вместимость

    // Увеличение capacity (если нужно)
    void GrowToFit(size_t required);

    // Вычисление следующей capacity (рост x2)
    static size_t NextCapacity(size_t current, size_t required);

public:
    // Конструктор по умолчанию
    // Инициализирует "пустое" состояние (data_ = nullptr)
    // все методы должны корректно работать с nullptr
    String();

    // Конструктор: строка из size одинаковых символов
    String(size_t size, char symbol);

    // Конструктор из C-строки
    // если s == nullptr → создаётся пустая строка
    String(const char* s);  // NOLINT

    // Конструктор из C-строки с ограничением длины
    // нельзя выходить за пределы s → используется безопасная длина
    String(const char* s, size_t size);

    // Конструктор копирования (deep copy)
    String(const String& other);

    // Конструктор перемещения (steal pointer)
    String(String&& other) noexcept;
    
    // Деструктор
    ~String();
    
    // Оператор копирующего присваивания
    String& operator=(const String& other);

    // Оператор перемещающего присваивания
    String& operator=(String&& other) noexcept;

    // Доступ по индексу (без проверки границ!)
    // UB если index >= size_
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    // Первый элемент
    // UB если строка пустая
    char& Front();
    const char& Front() const;

    // Последний элемент
    // UB если строка пустая
    char& Back();
    const char& Back() const;

    // C-style строка (может быть nullptr если строка пустая)
    char* CStr();
    const char* CStr() const;

    // Сырые данные
    char* Data();
    const char* Data() const;

    bool Empty() const;
    size_t Size() const;
    size_t Length() const;
    size_t Capacity() const;

    // Очистка строки (память НЕ освобождается)
    void Clear();

    // Обмен содержимым (O(1))
    void Swap(String& other);

    // Удаление последнего символа
    void PopBack();

    // Добавление символа в конец
    void PushBack(char symbol);

    // Конкатенация
    String& operator+=(const String& other);

    // Изменение размера
    void Resize(size_t new_size, char symbol = '\0');

    // Резервирование памяти
    void Reserve(size_t new_capacity);

    // Уменьшение capacity до size
    void ShrinkToFit();
};

// Конкатенация
String operator+(const String& lhs, const String& rhs);


// СРАВНЕНИЯ

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);

bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);

// ВВОД / ВЫВОД

std::ostream& operator<<(std::ostream& os, const String& s);
std::istream& operator>>(std::istream& is, String& s);