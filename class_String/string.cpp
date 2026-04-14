#include "string.hpp"

#include <algorithm>
#include <cctype>

// Безопасный strlen с ограничением
static size_t StrLen(const char* str, size_t max_len) {
    if (str == nullptr) {
        return 0;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        ++len;
    }
    return len;
}

// Конструктор по умолчанию
String::String() : data_(nullptr), size_(0), capacity_(0) {}

// Конструктор size + symbol
String::String(size_t size, char symbol) : data_(nullptr), size_(0), capacity_(0) {
    if (size == 0) {
        return;
    }

    data_ = new char[size + 1];
    size_ = size;
    capacity_ = size;

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = symbol;
    }

    data_[size_] = '\0';
}

// Конструктор из C-строки
String::String(const char* str) : data_(nullptr), size_(0), capacity_(0) {
    if (str == nullptr || str[0] == '\0') {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }

    data_ = new char[len + 1];
    size_ = len;
    capacity_ = len;

    for (size_t i = 0; i < len; ++i) {
        data_[i] = str[i];
    }

    data_[len] = '\0';
}

// Конструктор (str, size)
String::String(const char* str, size_t size) : data_(nullptr), size_(0), capacity_(0) {
    if (size == 0) {
        return;
    }

    size_t len = StrLen(str, size);  // StrLen гарантирует, что не выйдем за границы.

    data_ = new char[len + 1];
    size_ = len;
    capacity_ = len;

    for (size_t i = 0; i < len; ++i) {
        data_[i] = str[i];
    }

    data_[len] = '\0';
}

// Конструктор копирования
String::String(const String& other) : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ == 0) {
        return;
    }

    data_ = new char[other.size_ + 1];
    size_ = other.size_;
    capacity_ = other.size_;

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }

    data_[size_] = '\0';
}

// Конструктор перемещения
String::String(String&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

// Оператор присваивания копированием.
String& String::operator=(const String& other) {
    if (this == &other) {
        return *this;
    }

    if (other.size_ == 0) {
        Clear();
        return *this;
    }

    if (capacity_ < other.size_) {
        delete[] data_;
        data_ = new char[other.size_ + 1];
        capacity_ = other.size_;
    }

    size_ = other.size_;

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }

    data_[size_] = '\0';
    return *this;
}

// Перемещающее присваивание
String& String::operator=(String&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

// Деструктор
String::~String() {
    delete[] data_;
}

// Операторы доступа по индексу
char& String::operator[](size_t index) {
    return data_[index];
}

const char& String::operator[](size_t index) const {
    return data_[index];
}

// Доступ к первому символу.
char& String::Front() {
    return data_[0];
}

const char& String::Front() const {
    return data_[0];
}

// Доступ к последнему символу
char& String::Back() {
    return data_[size_ - 1];
}

const char& String::Back() const {
    return data_[size_ - 1];
}

// Возвращает указатель на внутренний буфер(C - строку)
char* String::CStr() {
    return data_;
}

const char* String::CStr() const {
    return data_;
}

char* String::Data() {
    return data_;
}

const char* String::Data() const {
    return data_;
}

// Проверка на пустую строку
bool String::Empty() const {
    return size_ == 0;
}

// Размер строки
size_t String::Size() const {
    return size_;
}

// Длина строки
size_t String::Length() const {
    return size_;
}

// Вместимость строки
size_t String::Capacity() const {
    return capacity_;
}

// Очистка строки: размер становится 0, но память не освобождается.
void String::Clear() {
    size_ = 0;

    if (data_ != nullptr) {
        data_[0] = '\0';
    }
}

// Обмен содержимым с другой строкой
void String::Swap(String& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

// Удаление последнего символа.
void String::PopBack() {
    if (size_ == 0) {
        return;
    }

    --size_;
    data_[size_] = '\0';
}

// Вычисление новой вместимости по мультипликативной схеме (коэффициент 2)
size_t String::NextCapacity(size_t current, size_t required) {
    size_t new_cap = (current == 0 ? 1 : current);

    while (new_cap < required) {
        new_cap *= 2;
    }

    return new_cap;
}

// Перевыделение памяти. Расширение буфера, если текущей вместимости недостаточно
void String::GrowToFit(size_t required) {
    if (required <= capacity_) {
        return;
    }

    size_t new_cap = NextCapacity(capacity_, required);

    char* new_data = new char[new_cap + 1];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;

    data_[size_] = '\0';
}

// Добавление символа в конец строки
void String::PushBack(char symbol) {
    GrowToFit(size_ + 1);

    data_[size_] = symbol;
    ++size_;
    data_[size_] = '\0';
}

// ⚠️ РАНЬШЕ БЫЛ RE:
// memcpy(... +1) → выход за границы
String& String::operator+=(const String& other) {
    if (other.size_ == 0) {
        return *this;
    }

    // FIX: self append
    if (this == &other) {
        String temp(other);
        return (*this += temp);
    }

    GrowToFit(size_ + other.size_);

    for (size_t i = 0; i < other.size_; ++i) {
        data_[size_ + i] = other.data_[i];
    }

    size_ += other.size_;
    data_[size_] = '\0';

    return *this;
}

// Изменение размера строки.
void String::Resize(size_t new_size, char symbol) {
    if (new_size <= size_) {
        size_ = new_size;

        if (data_ != nullptr) {
            data_[size_] = '\0';
        }
        return;
    }

    if (new_size > capacity_) {
        char* new_data = new char[new_size + 1];

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_size;
    }

    for (size_t i = size_; i < new_size; ++i) {
        data_[i] = symbol;
    }

    size_ = new_size;
    data_[size_] = '\0';
}

// Увеличение вместимости
void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    char* new_data = new char[new_capacity + 1];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;

    data_[size_] = '\0';
}

// Уменьшение вместимости
void String::ShrinkToFit() {
    if (size_ == 0) {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        return;
    }

    if (size_ == capacity_) {
        return;
    }

    char* new_data = new char[size_ + 1];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = size_;

    data_[size_] = '\0';
}

// Оператор конкатенации
String operator+(const String& lhs, const String& rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

// Вспомогательная функция для лексикографического сравнения
static int Compare(const String& lhs, const String& rhs) {
    size_t n = std::min(lhs.Size(), rhs.Size());

    for (size_t i = 0; i < n; ++i) {
        if (lhs[i] != rhs[i]) {
            return (lhs[i] < rhs[i]) ? -1 : 1;
        }
    }

    if (lhs.Size() < rhs.Size()) {
        return -1;
    }
    if (lhs.Size() > rhs.Size()) {
        return 1;
    }
    return 0;
}

bool operator==(const String& lhs, const String& rhs) {
    if (lhs.Size() != rhs.Size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
    return Compare(lhs, rhs) < 0;
}

bool operator>(const String& lhs, const String& rhs) {
    return Compare(lhs, rhs) > 0;
}

bool operator<=(const String& lhs, const String& rhs) {
    return Compare(lhs, rhs) <= 0;
}

bool operator>=(const String& lhs, const String& rhs) {
    return Compare(lhs, rhs) >= 0;
}

// Вывод в поток.
std::ostream& operator<<(std::ostream& os, const String& s) {
    for (size_t i = 0; i < s.Size(); ++i) {
        os << s[i];
    }
    return os;
}

// Ввод из потока.
std::istream& operator>>(std::istream& is, String& s) {
    s.Clear();

    char ch = 0;

    // пропуск пробелов
    while (is.get(ch)) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            break;
        }
    }

    if (!is) {
        return is;
    }

    s.PushBack(ch);

    while (is.get(ch)) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            break;
        }
        s.PushBack(ch);
    }

    return is;
}