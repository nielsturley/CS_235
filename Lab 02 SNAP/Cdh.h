
#ifndef LAB_02_SNAP_CDH_H
#define LAB_02_SNAP_CDH_H


class Cdh : public CourseName {
public:
    Cdh() {}
    Cdh(std::string courseName, std::string date, std::string time) {
        setCourseName(courseName);
        this->date = date;
        this->time = time;
    }
    ~Cdh() = default;
    std::string toString() const {
        std::ostringstream out;
        out << "cdh(" << getCourseName() << "," << date << "," << time << ")";
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Cdh& cdh) {
        os << cdh.toString();
        return os;
    }
    std::string getDate() const {
        return date;
    }
    std::string getTime() const {
        return time;
    }
private:
    std::string date;
    std::string time;
};


#endif //LAB_02_SNAP_CDH_H
