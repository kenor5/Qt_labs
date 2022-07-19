#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();

    return "";
}

// TODO: implement functions which are declared in Student.h.
double pointTrans(const double score) {
    int temp = score/10;
    switch(temp) {
        case 10: return 4.0;
        case 9: return 4.0;
        case 8: return 3.5;
        case 7: return 3.0;
        case 6: return 2.5;
        default: return 2.0;
    }
}

double Graduate::getGrade() {
    int totalPoint = 0;
    double totalSP = 0;

    for (std::vector<Class *>::iterator it = classes.begin();
         it != classes.end();
         it ++) {
        double temp_point = pointTrans((*it)-> getStudentWrapper(this->id).getScore());
        totalPoint += (*it)->point;
        totalSP += (*it)->point * temp_point;

    }
    return totalSP/totalPoint;

}


double Undergraduate::getGrade() {
    int totalPoint = 0;
    double totalSP = 0;

    for (std::vector<Class *>::iterator it = classes.begin();
         it != classes.end();
         it ++) {
        double temp_point = (*it)-> getStudentWrapper(this->id).getScore() / 20;
        totalPoint += (*it)->point;
        totalSP += (*it)->point * temp_point;

    }
    return totalSP/totalPoint;

}

