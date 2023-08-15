
#ifndef LAB_02_SNAP_CR_H
#define LAB_02_SNAP_CR_H


class Cr : public CourseName {
public:
    Cr() {}
    Cr(std::string courseName, std::string room) {
        setCourseName(courseName);
        this->room = room;
    }
    ~Cr() = default;
    std::string toString() const {
        std::ostringstream out;
        out << "cr(" << getCourseName() << "," << room << ")";
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Cr& cr) {
        os << cr.toString();
        return os;
    }
    std::string getRoom() const {
        return room;
    }
private:
    std::string room;
};


#endif //LAB_02_SNAP_CR_H
