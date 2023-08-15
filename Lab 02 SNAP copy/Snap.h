
#ifndef LAB_02_SNAP_SNAP_H
#define LAB_02_SNAP_SNAP_H



class Snap : public StudentID {
public:
    Snap() {}
    Snap(std::string studentID, std::string studentName, std::string studentAddress, std::string studentPhone) {
        setStudentID(studentID);
        this->studentName = studentName;
        this->studentAddress = studentAddress;
        this->studentPhone = studentPhone;
    }
    ~Snap() = default;
    std::string toString() const {
        std::ostringstream out;
        out << "snap(" << getStudentID() << "," << studentName << "," << studentAddress << "," << studentPhone << ")";
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Snap& snap) {
        os << snap.toString();
        return os;
    }
    std::string getStudentName() const {
        return studentName;
    }
    std::string getStudentAddress() const {
        return studentAddress;
    }
    std::string getStudentPhone() const {
        return studentPhone;
    }

private:
    std::string studentName;
    std::string studentAddress;
    std::string studentPhone;
};


#endif //LAB_02_SNAP_SNAP_H
