#pragma once
#include <exception>

class StringViewOutOfRange : public std::exception {
public:
	const char* what() const noexcept override {
		return "StringView out of range";
	}
};

class StringView {
	const char* data_;
	size_t size_;

public:
	StringView() : data_(nullptr), size_(0) {
	}

	StringView(const char* str) : data_(str), size_(0) {  //NOLINT
		if (str != nullptr) {
			while (str[size_] != '\0') {
				++size_;
			}
		}
	}

	StringView(const char* str, size_t size) : data_(str), size_(size) {
	}

	const char& operator[](size_t index) const {
		return data_[index];
	}

	bool operator==(const char* str) const {
		size_t i = 0;
		while (i < size_ && str[i] != '\0') {
			if (data_[i] != str[i]) {
				return false;
			}
			++i
		}
		return i == size_ && str[i] == '\0';
	}

	const char& Front() const {
		return data_[0];
	}

	const char& Back() const {
		return data_[size_ - 1];
	}

	size_t Size() const {
		return size_;
	}

	size_t Length() const {
		return size_;
	}

	bool Empty() const {
		return size_ == 0;
	}

	const char* Data() const {
		return data_;
	}

	void Swap(StringView& other) {
		const char* temp_data = data_;
		size_t temp_size = size_;

		data_ = other.data_;
		size_ = other.size_;

		other.data_ = temp_data;
		other.size_ = temp_size;
	}

	void RemovePrefix(size_t prefix_size) {
		if (prefix_size > size_) {
			prefix_size = size_;
		}
		data_ += prefix_size;
		size_ -= prefix_size;
	}

	void RemoveSuffix(size_t suffix_size) {
		if (suffix_size > size_) {
			suffix_size = size_;
		}
		size_ -= suffix_size;
	}

	StringView Substr(size_t pos, size_t count = static_cast<size_t>(-1)) const {
		if (pos > size_) {
			throw StringViewOutOfRange();
		}
		size_t max_len = size_ - pos;
		size_t len = (count < max_len) ? count : max_len;

		return {data_ + pos, len};
	}
};
