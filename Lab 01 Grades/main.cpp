#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC \
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif


//all std::names
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cerr;
using std::cout;
using std::string;
using std::istringstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::to_string;





int main(int argc, char* argv[]) {
    VS_MEM_CHECK


    //constants declared--used to determine what grade according to this scale:
    //  A >= (15 + average)
    //  (15 + average) > B > (5 + average)
    //  (5 + average) >= C >= (-5 + average)
    //  (-5 + average) > D > (-15 + average)
    //  (-15 + average >= E
    const int A_GRADE = 15;
    const int B_GRADE = 5;
    //const int C_GRADE = 0; but this isn't necessary for my code
    const int D_GRADE = -5;
    const int E_GRADE = -15;
    const int NUM_OF_AVAILABLE_GRADES = 5; //Students can receive one of 5 grades {A, B, C, D, E}

    //files opened from command line inputs
    ifstream in(argv[1]);
    ofstream out(argv[2]);

    //getting the # of students and # of exams
    int numStudents;
    int numExams;
    in >> numStudents >> numExams;

    //declaring a dynamic array of students names and a 2D dynamic array of student scores
    string *studentNames = new string[numStudents];
    int **studentScores = new int*[numStudents];
    for (int i = 0; i < numStudents; ++i) {
        studentScores[i] = new int[numExams];
    }

    //in.ignore(); for some reason I needed this extra one for my compiler to work
    in.ignore();
    //reading a line from the input text, separating the name from the scores, saving both to their respective arrays
    for (int i = 0; i < numStudents; ++i) {
        string line;
        getline(in, line);
        int p = 0;
        while (!isdigit(line[p])) {
            ++p;
        }
        studentNames[i] = line.substr(0, p);
        string scoreLine = line.substr(p);
        istringstream issLine(scoreLine);
        for (int q = 0; q < numExams; ++q) {
            issLine >> studentScores[i][q];
        }
    }


    in.close();
    //output Student Scores section
    out << "Student Scores:" << endl;
    for (int i = 0; i < numStudents; ++i) {
        out << setw(22) << studentNames[i];
        for (int q = 0; q < numExams; ++q) {
            out << fixed << setprecision(0) << setw(6) << studentScores[i][q];
        }
        out << endl;
    }

    //declaring a dynamic exam averages array, calculating and assigning averages to the array
    double *examAverages = new double[numExams];
    for (int q = 0; q < numExams; ++q) {
        double average = 0.0;
        for (int i = 0; i < numStudents; ++i) {
            average += studentScores[i][q]; //Summing all the scores for one exam
        }
        average /= numStudents; //Then finding the average
        examAverages[q] = average;
    }

    //outputting exam averages section
    out << "Exam Averages:" << endl;
    for (int q = 0; q < numExams; ++q) {
        out << setw(21) << "Exam " + to_string(q + 1) + " Average = ";
        out << fixed << setprecision(1) << setw(6) << examAverages[q] << endl;
    }

    //declaring a 2D dynamic array of student exam grades (as a string, for easier outputting)
    string **studentExamGrades = new string*[numStudents];
    for (int i = 0; i < numStudents; ++i) {
        studentExamGrades[i] = new string[numExams];
    }

    //declaring a 2D dynamic array of total exam grades--this is how many students got each grade for a given exam
    int **totalExamGrades = new int*[numExams];
    for (int q = 0; q < numExams; ++q) {
        totalExamGrades[q] = new int[NUM_OF_AVAILABLE_GRADES];
    }

    //had to initialize the totalExamGrades array as 0 because I don't always change the array
    for (int q = 0; q < numExams; ++q) {
        for (int l = 0; l < NUM_OF_AVAILABLE_GRADES; ++l) {
            totalExamGrades[q][l] = 0;
        }
    }

    //complicated way to determine what grade to assign a exam score,
    //save it in the right format (i.e. "90(A)"),
    //and increment the number of people who got that particular grade
    for (int q = 0; q < numExams; ++q) {
        for (int i = 0; i < numStudents; ++i) {
            if (studentScores[i][q] >= (A_GRADE + examAverages[q])) {
                studentExamGrades[i][q] = to_string(studentScores[i][q]) + "(A)";
                totalExamGrades[q][0] += 1; //0 referring to A grades
            }
            else if (studentScores[i][q] < (A_GRADE + examAverages[q]) && studentScores[i][q] > (B_GRADE + examAverages[q])) {
                studentExamGrades[i][q] = to_string(studentScores[i][q]) + "(B)";
                totalExamGrades[q][1] += 1; //1 referring to B grades
            }
            else if (studentScores[i][q] <= (B_GRADE + examAverages[q]) && studentScores[i][q] >= (D_GRADE + examAverages[q])) {
                studentExamGrades[i][q] = to_string(studentScores[i][q]) + "(C)";
                totalExamGrades[q][2] += 1; //2 referring to C grades
            }
            else if (studentScores[i][q] < (D_GRADE + examAverages[q]) && studentScores[i][q] > (E_GRADE + examAverages[q])) {
                studentExamGrades[i][q] = to_string(studentScores[i][q]) + "(D)";
                totalExamGrades[q][3] += 1; //3 referring to D grades
            }
            else if (studentScores[i][q] <= (E_GRADE + examAverages[q])) {
                studentExamGrades[i][q] = to_string(studentScores[i][q]) + "(E)";
                totalExamGrades[q][4] += 1; //4 referring to E grades
            }
        }
    }


    //Outputting student exam grades
    out << "Student Exam Grades:" << endl;
    for (int i = 0; i < numStudents; ++i) {
        out << setw(22) << studentNames[i];
        for (int q = 0; q < numExams; ++q) {
            out << fixed << setprecision(0) << setw(9) << studentExamGrades[i][q];
        }
        out << endl;
    }

    //Outputting exam grades (why can't they just use a consistent setw???)
    out << "Exam Grades:" << endl;
    for (int q = 0; q < numExams; q++) {
        out << setw(11) << "Exam  " + to_string(q + 1);
        out << setw(8) << to_string(totalExamGrades[q][0]) + "(A)";
        out << setw(8) << to_string(totalExamGrades[q][1]) + "(B)";
        out << setw(8) << to_string(totalExamGrades[q][2]) + "(C)";
        out << setw(8) << to_string(totalExamGrades[q][3]) + "(D)";
        out << setw(8) << to_string(totalExamGrades[q][4]) + "(E)";
        out << endl;
    }

    //Extra credit stuff--calculating total class average score
    double classAverageScore = 0.0;
    for (int i = 0; i < numStudents; ++i) {
        for (int q = 0; q < numExams; ++q) {
            classAverageScore += studentScores[i][q];
        }
    }
    classAverageScore /= (numStudents * numExams);

    //declaring dynamic student final grades array, calculating and assigning average score of each student to the array
    double *studentFinalGrades = new double[numStudents];
    for (int i = 0; i < numStudents; ++i) {
        double studentAverageScore = 0.0;
        for (int q = 0; q < numExams; ++q) {
            studentAverageScore += studentScores[i][q];
        }
        studentAverageScore /= numExams;
        studentFinalGrades[i] = studentAverageScore;
    }

    //outputting student final grades--maybe this is easier than using the string array from above
    out << "Student Final Grades:" << endl;
    for (int i = 0; i < numStudents; ++i) {
        out << setw(22) << studentNames[i];
        out << fixed << setprecision(1);
        if (studentFinalGrades[i] >= (classAverageScore + A_GRADE)) {
            out << setw(5) << studentFinalGrades[i] << "(A)";
        }
        else if (studentFinalGrades[i] < (classAverageScore + A_GRADE) && studentFinalGrades[i] > (classAverageScore + B_GRADE)) {
            out << setw(5) << studentFinalGrades[i] << "(B)";
        }
        else if (studentFinalGrades[i] <= (classAverageScore + B_GRADE) && studentFinalGrades[i] >= (classAverageScore + D_GRADE)) {
            out << setw(5) << studentFinalGrades[i] << "(C)";
        }
        else if (studentFinalGrades[i] < (classAverageScore + D_GRADE) && studentFinalGrades[i] > (classAverageScore + E_GRADE)) {
            out << setw(5) << studentFinalGrades[i] << "(D)";
        }
        else if (studentFinalGrades[i] <= (classAverageScore + E_GRADE)) {
            out << setw(5) << studentFinalGrades[i] << "(E)";
        }
        out << endl;
    }
    out << setw(20) << "Class Average Score =" << setw(6) << classAverageScore;
    out.close();

    //and deleting so Valgrind doesn't explode on me
    delete [] studentNames;
    for (int i = 0; i < numStudents; ++i) {
        delete [] studentScores[i];
    }
    delete [] studentScores;
    delete [] examAverages;
    for (int i = 0; i < numStudents; ++i) {
        delete [] studentExamGrades[i];
    }
    delete [] studentExamGrades;
    for (int q = 0; q < numExams; ++q) {
        delete [] totalExamGrades[q];
    }
    delete [] totalExamGrades;
    delete [] studentFinalGrades;

    return 0;
}
