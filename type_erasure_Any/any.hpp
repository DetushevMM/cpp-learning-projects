/*
# Проект 2: Any
В этом задании необходимо реализовать упрощенный аналог класса std::any с помощью механизма "type erasure" (стирание типов).

Детали реализации
- Для решения вам понадобится написать пустой (без полей) абстрактный базовый класс IHolder (Base) 
- и шаблонный класс AnyHolder<T> (Derived<T>) — наследник IHolder, который будет хранить в себе единственное поле типа T — требуемое значение. 
В свою очередь, AnyHolder должен поддерживать конструктор от T, чтобы инициализировать поле (будем считать, что у T есть конструктор копирования и/или move конструктор).

Основной класс Any должен иметь:
- Поле-указатель (умный) на IHolder;
- Конструктор по умолчанию, выставляющий указатель в nullptr (пустой объект);
- Конструктор копирования. Для удобства реализации, заведите в IHolder чисто виртуальный метод Clone(), который возвращает указатель на новый выделенный объект. 
  Естественно, нужно будет написать его реализацию в AnyHolder. Все копирование в итоге должно свестись к одному вызову Clone();
- Шаблонный конструктор от объекта произвольного типа T, который должен быть сохранен в Any. 
  Здесь нужно создать в куче объект AnyHolder<T> и присвоить его адрес полю-указателю на IHolder. 
  (Обращаем внимание, что здесь-то и произошло "стирание типа");
- Аналогичный оператор присваивания;
- Методы Swap(Any& other), 
- Reset() 
- и HasValue() (описания даны выше).
- Также реализуйте внешнюю шаблонную функцию template <class T> T AnyCast(const Any& value).
  Она возвращает значение, в случае, если IHolder указывает на AnyHolder<T> и бросает BadAnyCast в противном случае (вам наверняка пригодится dynamic_cast).
*/

#pragma once

#include <stdexcept>
#include <utility>
#include <typeinfo>
#include <memory>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {
 public:
  virtual std::unique_ptr<IHolder> Clone() const = 0;
  virtual ~IHolder() = default;
 };

 template <class T>
 class AnyHolder : public IHolder {
  T value_;

 public:
  explicit AnyHolder(const T& value) : value_(value) {
  }

  explicit AnyHolder(T&& value) : value_(std::move(value)) {
  }

  std::unique_ptr<IHolder> Clone() const override {
    return std::make_unique<AnyHolder<T>>(value_); 
  }

  const T& Value() const {
    return value_;
  }
 };

 class Any {
  std::unique_ptr<IHolder> holder_;

  template <class T>
  friend T AnyCast(const Any&);

 public:
  Any() = default;

  template <class T>
  explicit Any(T value) : holder_(new AnyHolder<T>(std::move(value))) {
  }

  Any(const Any& other) {
    if (other.holder_) {
      holder_ = other.holder_->Clone();
    }
  }

  Any(Any&& other) noexcept = default;

  Any& operator=(const Any& other) {
    if (this != &other) {
      if (other.holder_) {
        holder_ = other.holder_->Clone();
      } else {
        holder_.reset();
      }
    }
    return *this;
  }

  template <class T>
  Any& operator=(T value) {
    holder_ = std::make_unique<AnyHolder<T>>(std::move(value));
    return *this;
  }

  Any& operator=(Any&& other) noexcept = default;
  
  ~Any() = default;

  void Swap(Any& other) noexcept {
    holder_.swap(other.holder_);
  }

  void Reset() noexcept {
    holder_.reset();
  }

  bool HasValue() const noexcept {
    return holder_ != nullptr;
  }
};

template <class T>
T AnyCast(const Any& any) {
  if (auto ptr = dynamic_cast<const AnyHolder<T>*>(any.holder_.get())) {
    return ptr->Value();
  }
  throw BadAnyCast();
}

template <class T, class ...Args>
Any MakeAny(Args&&... args) {
  return Any(T(std::forward<Args>(args)...));
}
