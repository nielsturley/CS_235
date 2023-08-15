#ifndef LAB_09_POKEMON_SET_H
#define LAB_09_POKEMON_SET_H

#include "SetInterface.h"
#include "BST.h"

template<typename T>
class Set : public SetInterface<T> {
private:
	BST<std::string> set;
public:
	Set() = default;
	~Set() = default;

	bool insert(const T& item) {
		return set.addNode(item);
	}

	void clear() {
		set.clearTree();
	}

	size_t size() const {
		return set.size();
	}

	size_t count(const T& item) {
		if (set.search(item)) { return 1; }
		else { return 0; }
	}

	std::string toString() const {
		std::stringstream out;
		out << set;
		return out.str();
	}

	friend std::ostream& operator<< (std::ostream& os, const Set& set_) {
		os << set_.toString();
		return os;
	}
};
#endif //LAB_09_POKEMON_SET_H
