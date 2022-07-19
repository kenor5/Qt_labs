#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>


class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:


protected:
    const std::string name, year;

    double score;
    std::vector<Class *> classes;

public:
    virtual double getGrade() = 0;
    const std::string id;
    Degree degree;
    std::string toString() const;
    Student(const std::string id, const std::string name, const std::string year):name(name), year(year), id(id){}
    void addClass(Class *c) {
        classes.push_back(c);
    }

};

// TODO: implement class Graduate.
class Undergraduate: public Student{
    double pointTrans(const double score);
public:
    Undergraduate(const std::string id, const std::string name, const std::string year):Student(id, name, year){
        this->degree = undergraduate;
    }
    double getGrade() override;

};


// TODO: implement class Undergraduate.
class Graduate: public Student{
public:
    Graduate(const std::string id, const std::string name, const std::string year):Student(id, name, year){
        this->degree = graduate;
    }

    double getGrade() override;

};


class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    /*
    student和id都是const常量，初始化必须使用参数列表。
    */
    StudentWrapper(const std::string &id, const Student &student):student(student), id(id){

    }


    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
