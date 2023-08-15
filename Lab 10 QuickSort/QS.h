#ifndef QS_h
#define QS_h

#include "QSInterface.h"

template<typename T>
class QS : public QSInterface<T> {
private:
    size_t cap;
    size_t numItems;
    T* array;
    int numComparisons;
    int numExchanges;
public:
    QS() {
        clear();
        cap = 0;
        numItems = 0;
        numComparisons = 0;
        numExchanges = 0;
    }
    ~QS() { delete [] array; }
    
    void setCapacity(size_t c) {
        cap = c;
        array = new T[c];
    }
    
    bool addElement(T element) {
        if (numItems == cap) {
            reallocate();
        }
        array[numItems] = element;
        ++numItems;
        return true;
    }
    
    void reallocate() {
        T* newArray = new T[cap * 2];
        for (size_t i = 0; i < cap; ++i) {
            newArray[i] = array[i];
        }
        std::swap(newArray, array);
        delete [] newArray;
        cap *= 2;
    }
    
    bool sort(size_t left, size_t right) {
        int pivotIndex = medianOfThree(left, right);
        if (pivotIndex != -1) {
            pivotIndex = partition(left, right, pivotIndex);
            sort(left, pivotIndex);
            sort(pivotIndex, right);
        }
        return true;
    }
    
    void resetCounters() {
        numExchanges = 0;
        numComparisons = 0;
    }
    
    int getExchanges() const {
        return numExchanges;
    }
    
    int getComparisons() const {
        return numComparisons;
    }
    
    bool sortAll() {
        return sort(0, numItems);
    }
    
    bool clear() {
        delete [] array;
        array = new T[cap];
        numItems = 0;
        return true;
    }
    
    size_t capacity() const {
        return cap;
    }
    
    size_t size() const {
        return numItems;
    }
    
    int medianOfThree(size_t left, size_t right);
    
    int partition(size_t left, size_t right, size_t pivotIndex) {
        if (left >= pivotIndex || right <= pivotIndex || left < 0 || right > numItems) { return -1; }
        std::swap(array[left], array[pivotIndex]);
        //++numExchanges; //[3,7,19] (4,9,29)
        size_t up = left + 1;
        size_t down = right - 1;
        do {
            while ((array[left] >= array[up]) && (up != right - 1)) {
                ++up;
            }
            while ((array[left] < array[down]) && (down != left)) {
                --down;
            }
            if (up < down) {
                std::swap(array[up], array[down]);
                //++numExchanges; //[1,6,14]
            }
        }
        while (up < down);
        std::swap(array[left], array[down]);
        //++numExchanges; //[3,7,19] (4,9,29)
        return down;
    }
    
    std::string toString() const {
        std::ostringstream out;
        bool first = true;
        for (size_t i = 0; i < numItems; ++i) {
            if (first) {
                out << array[i];
                first = false;
            }
            else {
                out << "," << array[i];
            }
        }
        return out.str();
    }
    
    friend std::ostream& operator<< (std::ostream& os, const QS& qs) {
        os << qs.toString();
        return os;
    }
};

template<typename T>
int QS<T>::medianOfThree(size_t left, size_t right) {
	int middle = (left + right) / 2;
	if (left > middle || right < middle || left < 0 || right > numItems || left == right) { return -1; }
	right -= 1;
	if (array[left] > array[middle]) {
		if (array[middle] > array[right]) {
			//L>M>R --> R,M,L
			std::swap(array[left], array[right]);
			//++numExchanges; //[1,1,1]
		}
		else if (array[left] > array[right]) {
			//L>R>M --> M,R,L
			std::swap(array[left], array[middle]);
			std::swap(array[right], array[middle]);
			//++numExchanges;
			//++numExchanges; [0,0,0]
		}
		else {
			//R>L>M --> M,L,R
			std::swap(array[left], array[middle]);
			//++numExchanges; //[0,0,0]
		}
	}
	else {
		if (array[left] > array[right]) {
			//M>L>R --> R,L,M
			std::swap(array[left], array[middle]);
			std::swap(array[left], array[right]);
			//++numExchanges;
			//++numExchanges; [0,0,0]
		}
		else if (array[middle] > array[right]) {
			//M>R>L --> L,R,M
			std::swap(array[middle], array[right]);
			//++numExchanges; //[0,2,0]
		}
		else {
			//R>M>L --> L,M,R
			//++numExchanges; //[2,4,18]
		}
	}
	//++numExchanges; //[3,7,19]
	return middle;
}

#endif /* QS_h */
