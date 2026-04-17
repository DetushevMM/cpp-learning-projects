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
