#ifndef LAB_09_POKEMON_DEQUE_H
#define LAB_09_POKEMON_DEQUE_H

#define DEFAULT_CAPACITY 4

template <typename T>
class Deque {
private:
	size_t capacity;
	size_t numItems;
	size_t frontIndex;
	size_t rearIndex;
	T* data;

public:
	Deque() :
		capacity(DEFAULT_CAPACITY),
		numItems(0),
		frontIndex(0),
		rearIndex(DEFAULT_CAPACITY - 1),
		data(new T[DEFAULT_CAPACITY]) {}

	~Deque() {
		delete[] data;
	}

    void push_front(const T& value) {
		if (numItems == capacity) reallocate();
		++numItems;
		if (frontIndex == 0) {
			frontIndex = capacity - 1;
		}
		else {
			frontIndex = (frontIndex - 1) % capacity;
		}
		data[frontIndex] = value;
    }

    void push_back(const T& value) {
		if (numItems == capacity) reallocate();
		++numItems;
		rearIndex = (rearIndex + 1) % capacity;
		data[rearIndex] = value;
    }

    void pop_front() {
		if (empty()) throw std::string("Deque Empty!");
		--numItems;
		frontIndex = (frontIndex + 1) % capacity;
    }

    void pop_back() {
		if (empty()) throw std::string("Deque Empty!");
		--numItems;
		if (rearIndex == 0) {
			rearIndex = capacity - 1;
		}
		else {
			rearIndex = (rearIndex - 1) % capacity;
		}
    }
	T& front() {
		if (empty()) {
			throw std::string("Deque Empty!");
		}
		return data[frontIndex];
	}

    T& front2() const {
		if (empty()) {
			throw std::string("Deque Empty!");
		}
		return data[frontIndex];
    }

	T& back() {
		if (empty()) {
			throw std::string("Deque Empty!");
		}
		return data[rearIndex];
	}

    T& back2() const {
		if (empty()) {
			throw std::string("Deque Empty!");
		}
		return data[rearIndex];
    }

    size_t size() const {
		return numItems;
    }

    bool empty() const {
		if (numItems == 0) return true;
		else return false;
    }

	T& at(size_t index) {
		return data[(index + frontIndex) % capacity];
	}

    T& at2(size_t index) const {
		return data[(index + frontIndex) % capacity];
    }

    std::string toString() const {
		std::ostringstream out;
		for (size_t i = 0; i < numItems; ++i) {
			out << " " << at2(i);
		}
		return out.str();
    }

	friend std::ostream& operator<< (std::ostream& os, const Deque& deque) {
		os << deque.toString();
		return os;
	}

    void reallocate() {
		T* newData = new T[capacity * 2];
		for (size_t i = 0; i < numItems; ++i) {
			newData[i] = data[frontIndex];
			frontIndex = (frontIndex + 1) % capacity;
		}
		frontIndex = 0;
		rearIndex = numItems - 1;
		capacity = capacity * 2;
		std::swap(data, newData);
		delete[] newData;
	}

	int find(const T& id) const {
		int tag = -1;
		if (empty()) {
			return tag;
		}
		for (size_t i = 0; i < numItems; ++i) {
			if (id == at2(i)) {
				tag = i;
				break;
			}
		}
		return tag;
	}
};

#endif
