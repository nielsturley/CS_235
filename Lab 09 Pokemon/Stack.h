#ifndef LAB_09_POKEMON_STACK_H
#define LAB_09_POKEMON_STACK_H

#include "Deque.h"
template <typename T>
class Stack {
private:
	Deque<T> deque_;
public:
	Stack() {}
	~Stack() {}

	void push(const T& data) {
		deque_.push_front(data);
	}

	void pop() {
		deque_.pop_front();
	}

	T& top() const {
		return deque_.front2();
	}

	bool empty() const {
		return deque_.empty();
	}

	size_t size() const {
		return deque_.size();
	}

	T& at(const size_t index) const {
		return deque_.at2(index);
	}

	int find(const T& value) const {
		int tag = deque_.find(value);
		if (tag == -1) {
			return tag;
		}
		else {
			return size() - 1 - tag;
		}
	}

	std::string toString() const {
		std::ostringstream out;
		for (int i = size() - 1; i >= 0; --i) {
			out << " " << at(i).get_data();
		}
		return out.str();
	}

	friend std::ostream& operator<< (std::ostream& os, const Stack& stack) {
		os << stack.toString();
		return os;
	}
};

#endif
