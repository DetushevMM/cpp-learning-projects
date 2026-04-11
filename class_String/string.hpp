#pragma once

#include <cstddef>
#include <iosfwd>

class String {
private:
	char* data_;
	size_t size_;
	size_t capacity_;

	static size_t NextCapacity(size_t current, size_t required);
	void GrowToFit(size_t required);

public:
	String();
	String(size_t size, char symbol);
	String(const char* str);  // NOLINT
	String(const char* str, size_t size);

	String(const String& other);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	char& Front();
	const char& Front() const;
	char& Back();
	const char& Back() const;

	char* CStr();
	const char* CStr() const;

	const char* Data() const;
	char* Data();

	bool Empty() const;
	size_t Size() const;
	size_t Length() const;
	size_t Capacity() const;

	void Clear();
	void Swap(String& other);
	void PopBack();
	void PushBack(char symbol);

	String& operator+=(const String& other);

	void Resize(size_t new_size, char symbol);
	void Reserve(size_t new_capacity);
	void ShrinkToFit();
};

String operator+(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& os, const String& s);
std::istream& operator>>(std::istream& is, String& s);