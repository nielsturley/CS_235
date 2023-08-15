#ifndef LAB_06_RAILROAD_QUEUE_H
#define LAB_06_RAILROAD_QUEUE_H

#include "Deque.h"
template <typename T>
class Queue {
private:
	Deque<T> deque_;
public:
	Queue() {}
	~Queue() {}

	void push(const T& data) {
		deque_.push_back(data);
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
		return deque_.find(value);
	}

	std::string toString() const {
		return deque_.toString();
	}

	friend std::ostream& operator<< (std::ostream& os, const Queue& queue) {
		os << queue.toString();
		return os;
	}
};
#endif //LAB_06_RAILROAD_QUEUE_H
