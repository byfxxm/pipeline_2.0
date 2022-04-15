#pragma once

template<typename T, int N>
class RingBuffer {
public:
	void Reset() {
		read_index = write_index;
	}

	bool IsEmpty() {
		return read_index == write_index;
	}

	bool IsFull() {
		return (write_index + 1) % N == read_index;
	}

	bool Write(T t) {
		if (IsFull())
			return false;

		data_[write_index] = t;
		write_index = (write_index + 1) % N;
	}

	bool Read(T& t) {
		if (IsEmpty())
			return false;

		t = data_[read_index];
		read_index = (read_index + 1) % N;
	}

private:
	volatile int read_index{ 0 };
	volatile int write_index{ 0 };
	T data_[N];
};