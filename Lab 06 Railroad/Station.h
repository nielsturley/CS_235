#ifndef LAB_06_RAILROAD_STATION_H
#define LAB_06_RAILROAD_STATION_H

#include "Queue.h"
#include "Stack.h"
#include "Vector.h"

template <typename T>
class Station {
private:
	Queue<T> queue_;
	Stack<T> stack_;
	Vector<T> train_;
	T turntable_;
public:
	Station() : turntable_(-1) {} //initalizing turntable to a negative value. That's how I know it's empty
	~Station() {}

	void addStation(const T& value) {
		if (turntable_ != -1) {
			throw std::string("Turntable occupied!");
		}
		turntable_ = value;
	}

	void addQueue() {
		if (turntable_ == -1) {
			throw std::string("Turntable empty!");
		}
		queue_.push(turntable_);
		turntable_ = -1;
	}

	void addStack() {
		if (turntable_ == -1) {
			throw std::string("Turntable empty!");
		}
		stack_.push(turntable_);
		turntable_ = -1;
	}

	void addTrain() {
		if (turntable_ == -1) {
			throw std::string("Turntable empty!");
		}
		train_.push_back(turntable_);
		turntable_ = -1;
	}

	void removeQueue() {
		if (turntable_ != -1) {
			throw std::string("Turntable occupied!");
		}
		turntable_ = queue_.top();
		queue_.pop();
	}

	void removeStack() {
		if (turntable_ != -1) {
			throw std::string("Turntable occupied!");
		}
		turntable_ = stack_.top();
		stack_.pop();
	}

	std::string topStation() const {
		if (turntable_ == -1) {
			throw std::string("Turntable empty!");
		}
		std::ostringstream out;
		out << turntable_;
		return out.str();
	}

	std::string topQueue() const {
		std::ostringstream out;
		out << queue_.top();
		return out.str();
	}

	std::string topStack() const {
		std::ostringstream out;
		out << stack_.top();
		return out.str();
	}

	std::string sizeQueue() const {
		return std::to_string(queue_.size());
	}

	std::string sizeStack() const {
		return std::to_string(stack_.size());
	}

	std::string sizeTrain() const {
		return std::to_string(train_.size());
	}

	std::string queue() const {
		return queue_.toString();
	}

	std::string stack() const {
		return stack_.toString();
	}

	std::string train() const {
		return train_.toString();
	}

	std::string find(const T& value);

	std::string toString() const {
		std::string out;
		out += " " + std::to_string(turntable_);
		out += queue_.toString();
		out += stack_.toString();
		return out;
	}

	friend std::ostream& operator<< (std::ostream& os, const Station& station) {
		os << station.toString();
		return os;
	}
};

template<typename T>
std::string Station<T>::find(const T& value) {
	/**This function checks each place for the value.The find functions return a -1 (a "not here" index)
	 * if they don't find the car in their deque. If they do then that string is output.
	 * If all don't find the car then "Not Found" is output*/
	if (turntable_ == value) {
		return std::string("Turntable");
	}

	int queueVal = queue_.find(value);
	if (queueVal != -1) {
		return std::string("Queue[" + std::to_string(queueVal) + "]");
	}

	int stackVal = stack_.find(value);
	if (stackVal != -1) {
		return std::string("Stack[" + std::to_string(stackVal) + "]");
	}

	int trainVal = train_.find(value);
	if (trainVal != -1) {
		return std::string("Train[" + std::to_string(trainVal) + "]");
	}

	return std::string("Not Found!");
}

#endif //LAB_06_RAILROAD_STATION_H
