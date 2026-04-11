#include "string.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <utility>

namespace {

    size_t ClampedStrLen(const char* str, size_t max_len) {
        if (str == nullptr) {
            return 0;
        }
        size_t len = 0;
        while (len < max_len && str[len] != '\0') {
            ++len;
        }
        return len;
    }

}  // namespace

String::String() : data_(nullptr), size_(0), capacity_(0) {}

String::String(size_t size, char symbol)
    : data_(nullptr), size_(0), capacity_(0) {
    if (size == 0) {
        return;
    }
    data_ = new char[size + 1];
    size_ = size;
    capacity_ = size;
    std::memset(data_, symbol, size);
    data_[size] = '\0';
}

String::String(const char* str)  // NOLINT
    : data_(nullptr), size_(0), capacity_(0) {
    if (str == nullptr || str[0] == '\0') {
        return;
    }
    size_t len = std::strlen(str);
    data_ = new char[len + 1];
    size_ = len;
    capacity_ = len;
    std::memcpy(data_, str, len);
    data_[len] = '\0';
}

String::String(const char* str, size_t size)
    : data_(nullptr), size_(0), capacity_(0) {
    if (size == 0) {
        return;
    }
    size_t len = ClampedStrLen(str, size);
    data_ = new char[len + 1];
    size_ = len;
    capacity_ = len;
    if (len > 0) {
        std::memcpy(data_, str, len);
    }
    data_[len] = '\0';
}

String::String(const String& other) : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ == 0) {
        return;
    }
    data_ = new char[other.size_ + 1];
    size_ = other.size_;
    capacity_ = other.size_;
    std::memcpy(data_, other.data_, size_);
    data_[size_] = '\0';
}

String::String(String&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

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
    std::memcpy(data_, other.data_, size_);
    data_[size_] = '\0';
    return *this;
}

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

String::~String() { delete[] data_; }

char& String::operator[](size_t index) { return data_[index]; }

const char& String::operator[](size_t index) const { return data_[index]; }

char& String::Front() { return data_[0]; }

const char& String::Front() const { return data_[0]; }

char& String::Back() { return data_[size_ - 1]; }

const char& String::Back() const { return data_[size_ - 1]; }

char* String::CStr() { return data_; }

const char* String::CStr() const { return data_; }

const char* String::Data() const { return data_; }

char* String::Data() { return data_; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Length() const { return size_; }

size_t String::Capacity() const { return capacity_; }

void String::Clear() {
    size_ = 0;
    if (data_ != nullptr) {
        data_[0] = '\0';
    }
}

void String::Swap(String& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
    if (size_ == 0) {
        return;
    }
    --size_;
    data_[size_] = '\0';
}

size_t String::NextCapacity(size_t current, size_t required) {
    size_t new_cap = (current == 0) ? 1 : current;
    while (new_cap < required) {
        new_cap *= 2;
    }
    return new_cap;
}

void String::GrowToFit(size_t required) {
    if (required <= capacity_) {
        return;
    }
    size_t new_cap = NextCapacity(capacity_, required);
    char* new_data = new char[new_cap + 1];
    if (size_ > 0) {
        std::memcpy(new_data, data_, size_);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
    data_[size_] = '\0';
}

void String::PushBack(char symbol) {
    GrowToFit(size_ + 1);
    data_[size_] = symbol;
    ++size_;
    data_[size_] = '\0';
}

String& String::operator+=(const String& other) {
    if (other.size_ == 0) {
        return *this;
    }
    GrowToFit(size_ + other.size_);
    std::memcpy(data_ + size_, other.data_, other.size_);
    size_ += other.size_;
    data_[size_] = '\0';
    return *this;
}

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
        if (size_ > 0) {
            std::memcpy(new_data, data_, size_);
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

void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    char* new_data = new char[new_capacity + 1];
    if (size_ > 0) {
        std::memcpy(new_data, data_, size_);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    data_[size_] = '\0';
}

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
    std::memcpy(new_data, data_, size_);
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
    data_[size_] = '\0';
}

String operator+(const String& lhs, const String& rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

int Compare(const String& lhs, const String& rhs) {
    size_t n = std::min(lhs.Size(), rhs.Size());
    int cmp = std::memcmp(lhs.Data(), rhs.Data(), n);
    if (cmp != 0) {
        return cmp;
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
    return lhs.Size() == rhs.Size() &&
        std::memcmp(lhs.Data(), rhs.Data(), lhs.Size()) == 0;
}

bool operator!=(const String& lhs, const String& rhs) { return !(lhs == rhs); }

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

std::ostream& operator<<(std::ostream& os, const String& s) {
    if (s.Size() > 0) {
        os.write(s.Data(), static_cast<std::streamsize>(s.Size()));
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& s) {
    s.Clear();
    char ch = '\0';
    while (is.get(ch)) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            is.unget();
            break;
        }
    }
    if (!is) {
        return is;
    }
    while (is.get(ch)) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            is.unget();
            break;
        }
        s.PushBack(ch);
    }
    return is;
}