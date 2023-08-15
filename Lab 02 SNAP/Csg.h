
#ifndef LAB_02_SNAP_CSG_H
#define LAB_02_SNAP_CSG_H


class Csg : public CourseName, public StudentID {
public:
    Csg() {}
    Csg(std::string courseName, std::string studentID, std::string studentGrade) {
        setCourseName(courseName);
        setStudentID(studentID);
        this->studentGrade = studentGrade;
    }
    ~Csg() = default;
    std::string toString() const {
        std::ostringstream out;
        out << "csg(" << getCourseName() << "," << getStudentID() << "," << studentGrade << ")";
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Csg& csg) {
        os << csg.toString();
        return os;
    }
    std::string getStudentGrade() const {
        return studentGrade;
    }
private:
    std::string studentGrade;
};


#endif //LAB_02_SNAP_CSG_H
