/*
SharedPtr
Умные указатели реализуют важную идиому C++ — RAII (Resource Acquisition Is Initialization). 
Позволяют не заботиться о ручном управлении памятью, так как инкапсулируют управление ресурсами посредством конструкторов и деструкторов.

std::shared_ptr (C++11)
Шаблонный класс std::shared_ptr предоставляет интерфейс указателя на данные в динамической области с автоматическим контролем своевременного выделения и удаления ресурсов. 
В отличие от std::unique_ptr, std::shared_ptr реализует семантику разделяемого владения ресурсом. 
Это означает, что у одного ресурса может быть несколько равноправных владельцев. 
При этом гарантируется, что ресурс не будет освобожден пока существует хотя бы один его владелец (хотя бы один объект std::shared_ptr указывает на ресурс). 

Для решения проблемы циклических ссылок в язык также введены "слабые указатели" std::weak_ptr.
Они не считаются полноценными владельцами ресурса, но из них при необходимости можно получить "сильный указатель" std::shared_ptr на объект, если тот еще не удален.

Несмотря на то, что std::shared_ptr удобнее в использовании чем std::unique_ptr, на практике последний работает гораздо эффективней.
std::shared_ptr реализует дополнительную логику с подсчетом ссылок на объект. 
Поэтому std::shared_ptr стоит использовать только тогда, когда вам действительно нужно разделяемое владение.

Задание
Реализуйте шаблон SharedPtr — упрощенный аналог класса умного указателя с разделяемым владением.

Идея реализации: помимо самого указателя на выделенный ресурс необходимо знать число "сильных" и "слабых" ссылок на объект. 
Для этого в куче выделим счетчик strong_counter, который будет хранить эту информацию. 
- При создании нового указателя соответствующий счетчик увеличивается, при удалении — уменьшается; 
- если число сильных ссылок стало равно 0, то объект удаляется.

Шаблонный класс SharedPtr должен поддерживать:

- Конструктор по умолчанию (создает нулевой указатель);
- Конструктор от указателя (сохраняет указатель на владеемый объект);
- Конструктор копирования и копирующее присваивание (создают новую ссылку на тот же объект);
- Перемещающий конструктор и перемещающее присваивание должны передавать владение объектом;
- Метод Reset(T* ptr = nullptr), меняет указатель, которым владеет объект;
- Метод Swap(SharedPtr<T>&);
- Метод Get(), возвращающий указатель на владеемый объект;
- Метод UseCount(), возвращающий число "сильных" ссылок на объект;
- Операцию разыменовывания operator*;
- Операцию "стрелочка" operator->;
- Явную операцию приведения к bool (operator bool).

Замечания.

https://en.cppreference.com/w/cpp/memory/shared_ptr
Решение должно состоять из одного файла shared_ptr.hpp

Дополнительное задание 1
- Реализуйте шаблон WeakPtr — аналог std::weak_ptr.

Для поддержки "слабых" ссылок (см. выше) предлагается вынести счетчик обычных (сильных) ссылок strong_count в отдельную структуру Counter, 
в которую дополнительно добавить поле weak_count для подсчета количества слабых указателей, указывающих на данный объект. 
Как и ранее, сам счетчик (объект Counter) должен находиться в динамической памяти (вспомните почему), 
а указатель на него храниться в соответствующих объектах SharedPtr и WeakPtr. 

Логика освобождения ресурса теперь следующая:

- Если число сильных и слабых ссылок стало равно нулю, то удаляется и объект, и выделенный для него счетчик Counter.
- Если число сильных стало равно нулю при ненулевом числе слабых, то удаляется только объект, счетчик остается жить 
(то есть все сильные указатели уже "умерли", а некоторые слабые все еще ссылаются на данный счетчик).

Шаблон WeakPtr состоит из:

- Аналогичных конструкторов (по умолчанию, копирования, перемещения) и операций присваивания;
- Конструктора от SharedPtr (увеличивает число "слабых" ссылок);
- Метода Swap(WeakPtr<T>&);
- Метода Reset(), отвязывающего указатель от объекта;
- Метода UseCount(), возвращающего число "сильных" ссылок на объект;
- Метод Expired(), возвращающий true, если сильных ссылок на объект уже нет (объект удален);
- Метод Lock(), возвращающий SharedPtr на объект (если Expired() == true, то возвращается пустой указатель);

В SharedPtr необходимо добавить конструктор от WeakPtr, который работает аналогично методу Lock(), но в случае Expired() == true должно бросаться исключение BadWeakPtr.
Замечания.

https://en.cppreference.com/w/cpp/memory/weak_ptr
Для проверки этой части добавьте в файл с решением (shared_ptr.hpp) директиву #define WEAK_PTR_IMPLEMENTED

Дополнительное задание 2
Дополнительно можно реализовать внешнюю шаблонную функцию MakeShared, принимающую произвольное число параметров и возвращающую SharedPtr на объект созданный с помощью данных параметров конструктора. 
(Важно: в задании подойдет любая наивная реализация. На практике std::make_shared позволяет выделить счетчики и объект единым блоком в памяти, что часто повышает эффективность программы).

Для проверки этой части добавьте в файл с решением (shared_ptr.hpp) директиву #define MAKE_SHARED_IMPLEMENTED
*/

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