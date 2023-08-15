
#ifndef LAB_02_SNAP_COURSENAME_H
#define LAB_02_SNAP_COURSENAME_H



class CourseName {
public:
    CourseName() {}
    void setCourseName(std::string courseName) {
        this->courseName = courseName;
    }
    std::string getCourseName() const {
        return courseName;
    }
    virtual ~CourseName() {}
private:
    std::string courseName;
};
#endif //LAB_02_SNAP_COURSENAME_H
