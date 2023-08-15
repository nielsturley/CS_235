#ifndef LAB_06_RAILROAD_CAR_H
#define LAB_06_RAILROAD_CAR_H

struct Car {
	Car() = default;
    Car(unsigned int id) {
        this->id = id;
    }
    ~Car() = default;

	bool operator==(const Car car) const { return this->id == car.id; }
	bool operator!=(const Car car) const { return this->id != car.id; }

	unsigned int get_data() const {
		return id;
	}

	/** Return the Car as a string */
	std::string toString() const {
		return std::to_string(id);
	}

	/** Make insertion operator friend for a Car */
	friend std::ostream& operator<< (std::ostream& os, const Car& c)
	{
		os << c.toString();
		return os;
	}

    unsigned int id;
};

#endif //LAB_06_RAILROAD_CAR_H
