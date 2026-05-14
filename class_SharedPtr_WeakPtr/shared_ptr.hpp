#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

// Исключение для попытки создать SharedPtr из протухшего WeakPtr
class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
  T* ptr_;
  size_t* count_;       // количество SharedPtr
  size_t* weak_count_;  // количество WeakPtr

  friend class WeakPtr<T>;

  // Приватный конструктор используется внутри Lock(). Создает новый SharedPtr на уже существующий объект
  SharedPtr(T* ptr, size_t* count, size_t* weak_count) : ptr_(ptr), count_(count), weak_count_(weak_count) {
    if (count_) {
      *count_ += 1;
    }
  }

 public:
  // Конструктор по умолчанию - Пустой указатель
  SharedPtr() : ptr_(nullptr), count_(nullptr), weak_count_(nullptr) {
  }

  // Конструктор от указателя (сохраняет указатель на владеемый объект). Создание нового объекта
  explicit SharedPtr(T* ptr)
      : ptr_(ptr), count_(ptr ? new size_t(1) : nullptr), weak_count_(ptr ? new size_t(0) : nullptr) {
  }

  // Конструктор копирования
  SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_), weak_count_(other.weak_count_) {
    // Новый SharedPtr - увеличиваем количество на 1
    if (count_) {
      *count_ += 1;
    }
  }

  // Конструктор перемещения
  SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_), weak_count_(other.weak_count_) {
    // Старый объект становится пустым
    other.ptr_ = nullptr;
    other.count_ = nullptr;
    other.weak_count_ = nullptr;
  }

  // Конструктор от WeakPtr
  explicit SharedPtr(const WeakPtr<T>& wp) : SharedPtr() {
    if (wp.Expired()) {
      throw BadWeakPtr();
    }
    ptr_ = wp.ptr_;
    count_ = wp.count_;
    weak_count_ = wp.weak_count_;
    if (count_) {
      *count_ += 1;
    }
  }

  // Деструктор SharedPtr
  ~SharedPtr() {
    if (count_) {
      *count_ -= 1;
      if (*count_ + *weak_count_ == 0) {
        delete count_;
        delete weak_count_;
        delete ptr_;
      } else if (*count_ == 0) {
        delete ptr_;
      }
    }
  }

  // Копирующее присваивание
  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      auto temp = other;
      Swap(temp);
    }
    return *this;
  }

  // Перемещающее присваивание
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    auto temp = std::move(other);
    Swap(temp);
    return *this;
  }

  // Присваивание nullptr
  SharedPtr& operator=(std::nullptr_t) {
    Reset();
    return *this;
  }

  // Метод обмена значений
  void Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(count_, other.count_);
    std::swap(weak_count_, other.weak_count_);
  }

  // Метод меняет указатель, которым владеет объект;
  void Reset(T* ptr = nullptr) {
    // Создаем временный объект и меняемся с ним
    if (ptr_ == ptr) {
      return;
    }
    SharedPtr<T> temp(ptr);
    Swap(temp);
  }

  // Метод, возвращающий указатель на владеемый объект
  T* Get() const {
    return ptr_;
  }

  // Метод, возвращающий число "сильных" ссылок на объект
  size_t UseCount() const {
    return (count_ ? *count_ : 0);
  }

  // Операция разыменовывания
  T& operator*() const {
    return *ptr_;
  }

  // Операция "стрелочка"
  T* operator->() const {
    return ptr_;
  }

  // Явная операция приведения к bool
  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};

template <class T>
class WeakPtr {
  T* ptr_;
  size_t* count_;       // количество SharedPtr
  size_t* weak_count_;  // количество WeakPtr

  friend class SharedPtr<T>;

 public:
  // Коструктор по умолчанию
  WeakPtr() : ptr_(nullptr), count_(nullptr), weak_count_(nullptr) {
  }

  // Конструктор создания WeakPtr из SharedPtr
  explicit WeakPtr(const SharedPtr<T>& sp) : ptr_(sp.ptr_), count_(sp.count_), weak_count_(sp.weak_count_) {
    if (weak_count_) {
      *weak_count_ += 1;
    }
  }

  // Конструктор копирования
  WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), count_(other.count_), weak_count_(other.weak_count_) {
    // Новый SharedPtr - увеличиваем количество на 1
    if (weak_count_) {
      *weak_count_ += 1;
    }
  }

  // Конструктор перемещения
  WeakPtr(WeakPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_), weak_count_(other.weak_count_) {
    // Старый объект становится пустым
    other.ptr_ = nullptr;
    other.count_ = nullptr;
    other.weak_count_ = nullptr;
  }

  // Деструктор WeakPtr
  ~WeakPtr() {
    if (weak_count_) {
      *weak_count_ -= 1;
      if (*count_ + *weak_count_ == 0) {
        delete count_;
        delete weak_count_;
      }
    }
  }

  // Копирующее присваивание
  WeakPtr& operator=(const WeakPtr& other) {
    if (this != &other) {
      auto temp = other;
      Swap(temp);
    }
    return *this;
  }

  // Перемещающее присваивание
  WeakPtr& operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
      auto temp = std::move(other);
      Swap(temp);
    }
    return *this;
  }

  // Присваивание от SharedPtr
  WeakPtr& operator=(const SharedPtr<T>& sp) {
    WeakPtr temp(sp);
    Swap(temp);
    return *this;
  }

  // Метод обмена значений
  void Swap(WeakPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(count_, other.count_);
    std::swap(weak_count_, other.weak_count_);
  }

  // Метод, отвязывающий указатель от объекта;
  void Reset() {
    WeakPtr temp;
    Swap(temp);
  }

  // Метод, возвращающий число "сильных" ссылок на объект
  size_t UseCount() const {
    return (count_ ? *count_ : 0);
  }

  // Метод, возвращающий true, если сильных ссылок на объект уже нет (объект удален)
  bool Expired() const {
    return UseCount() == 0;
  }

  // Метод, возвращающий SharedPtr на объект (если Expired() == true, то возвращается пустой указатель)
  SharedPtr<T> Lock() const {
    return (Expired() ? SharedPtr<T>() : SharedPtr<T>(ptr_, count_, weak_count_));
  }
};

#define WEAK_PTR_IMPLEMENTED
#endif  // SHARED_PTR_HPP
