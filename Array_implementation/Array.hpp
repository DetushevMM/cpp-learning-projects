#pragma once

template <class T, size_t N>
class Array {
public:
	T data[N];

	T& operator[](size_t index) {
		return data[index];
	}
	
	const T& operator[](size_t index) const {
		return data[index];
	}

	T& Front() {
		return data[0];
	}

	const T& Front() const {
		return data[0];
	}

	T& Back() {
		return data[N - 1];
	}

	const T& Back() const {
		return data[N - 1];
	}
	T* Data() {
		return data;
	}

	const T* Data() const {
		return data;
	}

	size_t Size() const {
		return N;
	}

	bool Empty() const {
		return N == 0;
	}

	void Fill(const T& value) {
		for (size_t i = 0; i < N; ++i) {
			data[i] = value;
		}
	}

	void Swap(Array<T, N>& other) {
		for (size_t i = 0; i < N; ++i) {
			auto temp = data[i];
			data[i] = other.data[i];
			other.data[i] = temp;
		}
	}
};

template <class T>
size_t GetSize(const T&) {
	return 0;
}

template <class T, size_t N>
size_t GetSize(const T (&)[N]) {
	return N;
}

template <class T>
size_t GetRank(const T&) {
	return 0;
}

template <class T, size_t N>
size_t GetRank(const T (&arr)[N]) {
	return 1 + GetRank(arr[0]);
}

template <class T>
size_t GetNumElements(const T&) {
	return 1;
}

template <class T, size_t N>
size_t GetNumElements(const T (&arr)[N]) {
	return N * GetNumElements(arr[0]);
}
