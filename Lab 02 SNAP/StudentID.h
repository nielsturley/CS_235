
#ifndef LAB_02_SNAP_STUDENTID_H
#define LAB_02_SNAP_STUDENTID_H

//All the class member functions are pretty self-explanatory
#include <string>

class StudentID {
public:
    StudentID() {}
    void setStudentID(std::string studentID) {
        this->studentID = studentID;
    }
    std::string getStudentID() const {
        return studentID;
    }
    virtual ~StudentID() {}
private:
    std::string studentID;
};

#endif //LAB_02_SNAP_STUDENTID_H
