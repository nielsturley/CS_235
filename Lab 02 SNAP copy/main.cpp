#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "StudentID.h"
#include "CourseName.h"
#include "Snap.h"
#include "Csg.h"
#include "Cdh.h"
#include "Cr.h"




using std::ifstream;
using std::ofstream;
using std::string;
using std::endl;
using std::cout;
using std::ostream;
using std::vector;



int main(int argc, char* argv[]) {
    //inputting the command line prompts as input and output
    ifstream in(argv[1]);
    ofstream out(argv[2]);


    //creating vectors for the different classes
    vector<Snap> snaps;
    vector<Csg> csgs;
    vector<Cdh> cdhs;
    vector<Cr> crs;

    //Inputting lines from the in file. Outputting the line received (throwing an error if invalid format).
    //Then sectioning the line into distinct segments and feeding those segments into a class constructor
    //which is then saved to the requisite vector.
    out << "Input Strings:" << endl;
    while (!in.eof()) {
        try {
            for (string line; getline(in, line);)
            {
                if ("snap(" == line.substr(0, 5)) {
                    out << line << endl;
                    line = line.substr(line.find('(') + 1);
                    string studentID = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string studentName = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string studentAddress = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string studentPhone = line.substr(0, line.find(')'));
                    snaps.push_back(Snap(studentID, studentName, studentAddress, studentPhone));
                }
                else if ("csg(" == line.substr(0, 4)) {
                    out << line << endl;
                    line = line.substr(line.find('(') + 1);
                    string courseName = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string studentID = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string studentGrade = line.substr(0, line.find(')'));
                    csgs.push_back(Csg(courseName, studentID, studentGrade));
                }
                else if ("cdh(" == line.substr(0, 4)) {
                    out << line << endl;
                    line = line.substr(line.find('(') + 1);
                    string courseName = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string day = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string time = line.substr(0, line.find(')'));
                    cdhs.push_back(Cdh(courseName, day, time));
                }
                else if ("cr(" == line.substr(0, 3)) {
                    out << line << endl;
                    line = line.substr(line.find('(') + 1);
                    string courseName = line.substr(0, line.find(','));
                    line = line.substr(line.find(',') + 1);
                    string room = line.substr(0, line.find(')'));
                    crs.push_back(Cr(courseName, room));
                }
                else {
                    throw line;
                }
            }
        }
        catch (string errorString) {
            out << "**Error: " << errorString << endl;
        }
    }

    //Outputting the contents of all the vectors using the << operator
    out << endl << "Vectors:" << endl;
    for (unsigned int i = 0; i < snaps.size(); ++i) {
        out << snaps.at(i) << endl;
    }
    for (unsigned int i = 0; i < csgs.size(); ++i) {
        out << csgs.at(i) << endl;
    }
    for (unsigned int i = 0; i < cdhs.size(); ++i) {
        out << cdhs.at(i) << endl;
    }
    for (unsigned int i = 0; i < crs.size(); ++i) {
        out << crs.at(i) << endl;
    }

    //Outputting the course grades by looping through the snaps vector to find
    //the students that have the IDs listed in the csgs vector
    out << endl << "Course Grades:" << endl;
    for (unsigned int i = 0; i < csgs.size(); ++i) {
        out << csgs.at(i).getCourseName() << ",";
        for (unsigned int j = 0; j < snaps.size(); ++j) {
            if (snaps.at(j).getStudentID() == csgs.at(i).getStudentID()) {
                out << snaps.at(j).getStudentName();
                break;
            }
        }
        out << "," << csgs.at(i).getStudentGrade() << endl;
    }

    //Outputting the student schedules (I hate nested loops. So. Freaking. Much.)
    out << endl << "Student Schedules:" << endl;
    for (unsigned int i = 0; i < snaps.size(); ++i) {
        out << snaps.at(i).getStudentName() << ", " << snaps.at(i).getStudentID() << ", "
            << snaps.at(i).getStudentAddress() << ", " << snaps.at(i).getStudentPhone() << endl; //Outputting the student info
        for (unsigned int j = 0; j < csgs.size(); ++j) {
            if (snaps.at(i).getStudentID() == csgs.at(j).getStudentID()) { //Finding the courses the student is in using studentID
                out << "  " << csgs.at(j).getCourseName() << " ";
                for (unsigned int k = 0; k < cdhs.size(); ++k) {
                    if (csgs.at(j).getCourseName() == cdhs.at(k).getCourseName()) { //Finding the dates of the course
                        out << cdhs.at(k).getDate(); //no break here because you have to list all the days the class happens (M AND W AND F)
                    }
                }
                for (unsigned int k = 0; k < cdhs.size(); ++k) { //Finding the time of the course
                    if (csgs.at(j).getCourseName() == cdhs.at(k).getCourseName()) {
                        out << " " << cdhs.at(k).getTime();
                        break;
                    }
                }
                for (unsigned int k = 0; k < crs.size(); ++k) {
                    if (csgs.at(j).getCourseName() == crs.at(k).getCourseName()) { //Finding the room of the course
                        out << ", " << crs.at(k).getRoom() << endl;
                        break;
                    }
                }
            }
        }
        out << endl;
    }
    in.close();
    out.close();

    return 0;
}
