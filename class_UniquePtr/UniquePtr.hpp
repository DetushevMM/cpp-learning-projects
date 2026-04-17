/*
UniquePtr
Умные указатели реализуют важную идиому C++ — RAII (Resource Acquisition Is Initialization) и позволяют не заботиться о ручном управлении памятью, так как
инкапсулируют управление ресурсами посредством конструкторов и деструкторов.

std::unique_ptr (C++11)
С++ предоставляет шаблонный класс std::unique_ptr
(https://en.cppreference.com/w/cpp/memory/unique_ptr) для безопасной работы с динамически выделенной памятью (и другими ресурсами). 
В std::unique_ptr перегружены все необходимые операции для комфортной работы с объектами так, как если бы это были обычные указатели (которые еще и память за собой очищают).
Объекты этого класса считаются единственными владельцами ресурса, на который они
указывают, поэтому эти объекты нельзя копировать, но можно перемещать — передавать владение другому объекту. 
Использование std::unique_ptr почти не накладывает дополнительных вычислительных расходов, поэтому пользоваться им так же эффективно,
как и обычными указателями, и при этом гораздо безопаснее.

#include <memory>
// ...
std::unique_ptr<int> ptr(new int(10));
std::cout << *ptr << '\n';  // 10

// std::unique_ptr<int> copy = ptr; копирование запрещено
std::unique_ptr<int> moved = std::move(ptr);  // теперь ptr пуст
std::cout << *moved << '\n';  // 10

auto rational = std::make_unique<Rational>(1, 2);
// эквивалентно std::unique_ptr<Rational> rational(new Rational(1, 2));
std::cout << rational->Numerator() << ' ' << rational->Denominator() << '\n'; //
1 2

// delete вызовутся автоматически в деструкторах!

Задание
Реализуйте шаблон UniquePtr — упрощенный аналог класса умного указателя с уникальным владением, std::unique_ptr (C++11).

Детали реализации
Шаблонный класс должен поддерживать:

- Конструктор по умолчанию (создает нулевой указатель);
- Конструктор от указателя (сохраняет указатель на объект);
- Конструктор копирования и копирующее присваивание должны отсутствовать (= delete);
- Перемещающий конструктор и перемещающее присваивание должны передавать владение объектом;
- Метод Release(), который отлучает класс от владения текущим ресурсом и возвращает указатель на него;
- Метод Reset(T* ptr = nullptr), меняет указатель, которым владеет объект (старый ресурс удаляется);
- Метод Swap(UniquePtr<T>&);
- Метод Get(), возвращающий указатель на объект;
- Оператор разыменовывания operator*;
- Оператор "стрелочка" operator->;
- Явный оператор приведения к bool (operator bool).
- Дополнительно можете реализовать внешнюю шаблонную функцию MakeUnique,
  Она принимает произвольное число параметров и возвращающую UniquePtr на объект созданный с помощью данных параметров конструктора. 
  В этом случае добавьте в файл с решением директиву #define MAKE_UNIQUE_IMPLEMENTED.

Замечания.
https://en.cppreference.com/w/cpp/memory/unique_ptr
Решение должно состоять из одного файла unique_ptr.hpp
*/

#pragma once

#include <utility>

template <class T> class UniquePtr {
  T *ptr_;

 public:
  // Конструктор по умолчанию
  UniquePtr() : ptr_(nullptr) {}

  // Конструктор от указателя
  explicit UniquePtr(T* pointer) : ptr_(pointer) {}

  // Выключенный конструктор копирования
  UniquePtr(const UniquePtr& other) = delete;

  // Выключенное копирующее присваивание
  UniquePtr operator=(const UniquePtr& other) = delete;

  // Перемещающий конструктор
  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  // Перемещающее присваивание
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
  }

  // Деструктор
  ~UniquePtr() {
    delete ptr_;
  }

  // Метод Release() - отлучает класс от владения текущим ресурсом и возвращает указатель на него
  T* Release() {
    T* pointer = ptr_;
    ptr_ = nullptr;
    return pointer;
  }

  // Метод Reset меняет указатель, которым владеет объект (старый ресурс удаляется)
  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }
  // Метод Swap
  void Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
  }

  // Метод Get(), возвращающий указатель на объект
  T* Get() const {
    return ptr_;
  }

  // Оператор разыменовывания operator*
  T& operator*() const {
    return *ptr_;
  }

  // Оператор "стрелочка" operator->
  T* operator->() const {
    return ptr_;
  }
  
  // Явный оператор приведения к bool (operator bool)
  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};

#define MAKE_UNIQUE_IMPLEMENTED

// Внешняя шаблонная функция MakeUnique принимает произвольное число параметров и возвращающую UniquePtr на объект созданный конструктором
template <typename T, typename... U>
UniquePtr<T> MakeUnique(U&&... args) {
  return UniquePtr<T>(new T(std::forward<U>(args)...));
}