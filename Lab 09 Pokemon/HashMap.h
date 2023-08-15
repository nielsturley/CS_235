#ifndef LAB_09_POKEMON_HASHMAP_H
#define LAB_09_POKEMON_HASHMAP_H

#include "HashMapInterface.h"
#include "Pair.h"
#include "Set.h"
#include <cmath>

template<typename K, typename V>
class HashMap : public HashMapInterface<K,V> {
private:
	size_t capacity;
	size_t numPairs;
	Pair<K,V>* pairs;
public:
	HashMap() :
		capacity(DEFAULT_MAP_HASH_TABLE_SIZE),
		numPairs(0),
		pairs(new Pair<K,V>[DEFAULT_MAP_HASH_TABLE_SIZE]) {}

	~HashMap() { delete[] pairs; }

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	V& operator[](const K& key);

	/** @return: the number of elements that match the key in the Map. */
	size_t count(const K& key) {
		long long hashIndex = calculateHash(key);
		if (pairs[hashIndex].first == key) { return 1; }
		else { return 0; }
	}

	/** Removes all items from the Map. */
	void clear();

	/** @return: number of Key-Value pairs stored in the Map. */
	size_t size() const {
		return numPairs;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	size_t max_size() const {
		return capacity;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	std::string toString() const {
		std::stringstream out;
		for (size_t i = 0; i < capacity; ++i) {
			if (pairs[i].first.length() != 0) {
				out << "  [" << i << ":" << pairs[i].first << "->" << pairs[i].second << "]\n";
			}
		}
		return out.str();
	}

	friend std::ostream& operator<< (std::ostream& os, const HashMap& hashMap) {
		os << hashMap.toString();
		return os;
	}

	//hash calculation
	long long calculateHash(const K& key) const {
		long long hash = 0;
		for (unsigned int i = 0; i < key.size(); ++i) {
			hash += (key[i] * pow(HASH_CONSTANT, (key.size() - 1 - i)));
		}
		hash = hash % capacity;
		return hash;
	}

	//well, it's supposed to reallocate
	//instead it reorders, leaks memory, and doesn't work with Sets
	//If you know how to fix it, lemme know cause rn my solution is to throw my laptop at the wall
	void reallocate();

};


template<>
void HashMap<std::string, Set<std::string>>::clear() { //clear for string, Set
	for (size_t i = 0; i < capacity; ++i) {
		if (pairs[i].first.length() != 0) {
			pairs[i].first = "";
			pairs[i].second.clear();
		}
	}
	numPairs = 0;
}

template<typename K, typename V>
void HashMap<K, V>::reallocate() {
	size_t oldCapacity = capacity;
	capacity = capacity * 2;
	//std::cout << "Reallocating: " << oldCapacity << " to " << capacity << std::endl;
	Pair<K,V>* newPairs = new Pair<K,V>[capacity];
	for (size_t i = 0; i < oldCapacity; ++i) {
		int k = -1;
		long long hashIndex = calculateHash(pairs[i].first);
		if (pairs[i].first.length() == 0) {
			//std::cout << "i[" << i << "]: empty" << std::endl;
			continue;
		}
		//std::cout << "i[" << i << "]: New hashIndex of " << pairs[i].first << ": " << hashIndex << std::endl;
		while (true) {
			if (newPairs[hashIndex].first.length() == 0) {
				//std::cout << "Empty spot found at: " << hashIndex << std::endl;
				newPairs[hashIndex].first = pairs[i].first;
				newPairs[hashIndex].second = pairs[i].second;
				break;
			}
			//std::cout << "Collision of: " << pairs[i].first << " with " << newPairs[hashIndex].first << std::endl;
			k += 2;
			hashIndex = (hashIndex + k) % capacity;
		}
	}
	pairs = newPairs;
	delete[] newPairs;
}

template<typename K, typename V>
V &HashMap<K, V>::operator[](const K &key) {
	long long hashIndex = calculateHash(key);
	int k = -1;
	int num = numPairs * 100;
	int cap = capacity;
	int load = num / cap;
	if (load > LOAD_THRESHOLD) {
		reallocate();
	}
	while (true) {
		//std::cout << "Hashing: " << key << ", index of " << hashIndex << std::cout;
		if (pairs[hashIndex].first.length() == 0) {
			//std::cout << "Empty spot found at: " << hashIndex;
			pairs[hashIndex].first = key;
			++numPairs;
			break;
		}
		if (pairs[hashIndex].first == key) {
			break;
		}
		//std::cout << "Collision of: " << pairs[hashIndex].first << " with " << key << std::cout;
		k += 2;
		hashIndex = (hashIndex + k) % capacity;
	}
	return pairs[hashIndex].second;
}

template<>
void HashMap<std::string, std::string>::clear() { //clear for string, string
	for (size_t i = 0; i < capacity; ++i) {
		if (pairs[i].first.length() != 0) {
			pairs[i].first = "";
			pairs[i].second = "";
		}
	}
	numPairs = 0;
}
#endif //LAB_09_POKEMON_HASHMAP_H
