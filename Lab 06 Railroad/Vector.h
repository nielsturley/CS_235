#ifndef LAB_06_RAILROAD_VECTOR_H
#define LAB_06_RAILROAD_VECTOR_H

#include "Deque.h"
template <typename T>
class Vector {
private:
	Deque<T> deque_;
public:
	void push_back(const T& value) {
		deque_.push_back(value);
	}

	void pop_back() {
		deque_.pop_back();
	}

	T& back() const {
		return deque_.back2();
	}

	size_t size() const {
		return deque_.size();
	}

	T& at(const size_t index) const {
		return deque_.at2(index);
	}

	int find(const T& value) const {
		return deque_.find(value);
	}

	std::string toString() const {
		return deque_.toString();
	}

	friend std::ostream& operator<< (std::ostream& os, const Vector& vector) {
		os << vector.toString();
		return os;
	}
};
#endif //LAB_06_RAILROAD_VECTOR_H
